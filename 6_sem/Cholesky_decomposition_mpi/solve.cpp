#include "solve.h"
#include "block_action.h"
#include "matr_operation.h"

#include "in_out.h"

int
MPI_solve (size_arguments &size_args, matr *ptr_columns, vect D)
{
  int err = NO_ERROR;
  double norm = 1;

  // === memory allocation === //
  std::unique_ptr <double []> ptr_diag_inv;
  ptr_diag_inv = std::make_unique <double []> (size_args.block_lim * size_args.squared_block_size);
  buff_ptr diag_inv = ptr_diag_inv.get ();


  //TODO norm = norm_A ();
  printf_main_process ("\nMatrix norm = %f\n", norm);

  err = MPI_cholesky (size_args, ptr_columns, D, diag_inv, norm * EPS);
  if (err != NO_ERROR)
    return err;

  /* TODO
   * calc_y
   * DB
   * calc_x
   * memcpy (X, B, matrix_size * sizeof (double)); */

  return err;
}


int
MPI_cholesky (size_arguments &size_args, matr *ptr_columns, vect D, buff_ptr diag_inv, double eps)
{
  int owner, err = NO_ERROR, send_count = 0;;
  matr_bl R_i = nullptr, R_i_inv;

  // === memory allocation === //
  std::unique_ptr <double []> ptr_R_col, ptr_R_is_buf, ptr_R_js_buf;

  ptr_R_col = std::make_unique <double []> (size_args.buff_column_size);
  ptr_R_is_buf = std::make_unique <double []> (size_args.squared_block_size);
  ptr_R_js_buf = std::make_unique <double []> (size_args.squared_block_size);

  column_bl R_col = ptr_R_col.get ();
  matr_bl R_is_buf = ptr_R_is_buf.get ();
  matr_bl R_js_buf = ptr_R_js_buf.get ();


  // === cholesky decomposition === //
  for (int i_bl = 0; i_bl < size_args.block_lim; i_bl++)
    {
      // === get i-th column -> R_col and send === //
      owner = size_args.get_column_owner (i_bl);

      if (size_args.is_my_column (i_bl))
        get_column (i_bl, size_args, ptr_columns, R_col);

      if (i_bl != size_args.div)
        send_count += size_args.squared_block_size;
      else
        send_count = size_args.buff_column_size;

      MPI_Bcast (R_col, send_count, MPI_DOUBLE, owner, MPI_COMM_WORLD);


      // === calculate diag block R_{ii} === //
      err = calc_diag_block_R (i_bl, size_args, D, R_col, eps);
      if (err != NO_ERROR)
        return err;

      R_i = R_col + i_bl * size_args.squared_block_size;
      if (size_args.is_my_column (i_bl))
        put_diag_block (i_bl, size_args, ptr_columns, R_i);


      // === inverse diag block R_{ii} -> Ri_inv === //
      R_i_inv = diag_inv + i_bl * size_args.squared_block_size;
      err = inverse_upper_matrix (size_args.get_col_width (i_bl), size_args.block_size, R_i, R_i_inv, eps);
      if (err != NO_ERROR)
        return err;


      // === calculate others block R_{is} ->  === //
      for (int s_bl = size_args.get_start_ind (i_bl); s_bl < size_args.block_lim; s_bl +=size_args.comm_size)
        calc_full_block_R (i_bl, s_bl, size_args, ptr_columns, D, R_col, R_i_inv, R_is_buf, R_js_buf);

    }

  return err;
}


int
cholesky (int size, int shift, matr A, vect D, double eps)
{
  int i, j, k;
  double sum[4];
  double D_k, R_ii, inv_D_i_R_ii, sum_;
  matr pA_i_i = A, pA_i_j, pA_k_i, pA_k_j;

  for (i = 0; i < size; i++, pA_i_i += shift + 1)
    {
      sum_ = pA_i_i[0];

      pA_k_i = &A[i];
      for (k = 0; k < i; k++, pA_k_i += shift)
        sum_ -= pA_k_i[0] * D[k] * pA_k_i[0];


      if (is_small (sum_, eps))
        return ERROR_EPS;

      D[i] = (sum_ > 0) ? 1 : -1;
      R_ii = sqrt (fabs (sum_));

      inv_D_i_R_ii = D[i] / R_ii;
      pA_i_i[0] = R_ii;

      pA_i_j = pA_i_i + 1;
      for (j = i + 1; j < size - 3; j += 4, pA_i_j += 4)
        {
          sum[0] = pA_i_j[0];
          sum[1] = pA_i_j[1];
          sum[2] = pA_i_j[2];
          sum[3] = pA_i_j[3];

          pA_k_i = &A[i];
          pA_k_j = &A[j];

          for (k = 0; k < i; k++)
            {
              D_k = D[k];

              sum[0] -= pA_k_i[0] * D_k * pA_k_j[0];
              sum[1] -= pA_k_i[0] * D_k * pA_k_j[1];
              sum[2] -= pA_k_i[0] * D_k * pA_k_j[2];
              sum[3] -= pA_k_i[0] * D_k * pA_k_j[3];

              pA_k_i += shift;
              pA_k_j += shift;
            }

          pA_i_j[0] = sum[0] * inv_D_i_R_ii;
          pA_i_j[1] = sum[1] * inv_D_i_R_ii;
          pA_i_j[2] = sum[2] * inv_D_i_R_ii;
          pA_i_j[3] = sum[3] * inv_D_i_R_ii;
        }

      for (; j < size; j++, pA_i_j++)
        {
          sum[0] = pA_i_j[0];

          for (k = 0; k < i; k++)
            sum[0] -= A[k * shift + i] * D[k] * A[k * shift + j];

          pA_i_j[0] = sum[0] * inv_D_i_R_ii;
        }
    }

  return NO_ERROR;
}


// ======================================== calculate block R ======================================= //
int
calc_diag_block_R (int ind_bl, size_arguments &size_args, vect D, column_bl R_col, double eps)
{
  vect_bl D_j = D;
  matr_bl R_ji = R_col;
  matr_bl R_i = R_col + ind_bl * size_args.squared_block_size;

  for (int j_bl = 0 ; j_bl < ind_bl; j_bl++)
    {
      A_minus_RtDR (size_args.block_size, R_i, R_ji, D_j, R_ji);
      R_ji += size_args.squared_block_size;
      D_j += size_args.block_size;
    }

  return cholesky (size_args.get_col_width (ind_bl), size_args.block_size, R_i, D_j, eps);
}


void
calc_full_block_R (int i_bl, int s_bl, size_arguments &size_args,  matr *ptr_columns, vect D,
                   column_bl R_col_i, matr_bl Ri_inv, matr_bl R_is, matr_bl R_js)
{
  vect_bl D_j = D;
  matr_bl R_ji = R_col_i;

  get_full_block (i_bl, s_bl, size_args, ptr_columns, R_is);

  for (int j_bl = 0 ; j_bl < i_bl; j_bl++)
    {
      get_full_block (j_bl, s_bl, size_args, ptr_columns, R_js);
      A_minus_RtDR (size_args.block_size, R_is, R_ji, D_j, R_js);
      R_ji += size_args.squared_block_size;
      D_j += size_args.block_size;
    }

  DRtA (size_args.block_size, D_j, Ri_inv, R_is);
  put_full_block (i_bl, s_bl, size_args, ptr_columns, R_is);
}


//void
//calc_full_block_R (int matrix_size, int block_size, matr A, vect D,
//                   matr_bl Ri_inv, vect_bl D_i, matr_bl R_is, column R_col,
//                   matr_bl R_bl, vect_bl D_bl, int i, int s, int div, int mod)
//{
//  int j, shift = block_size * block_size;
//  matr_bl R_ji = R_col;

//  for (j = 0 ; j < i; j++, R_ji += shift)
//    {
//      get_full_block (matrix_size, block_size, A, R_bl, j, s, div, mod);
//      get_vect_block (block_size, D, D_bl, j, div, mod);
//      A_minus_RtDR (block_size, R_is, R_ji, D_bl, R_bl);
//    }

//  DRtA (block_size, D_i, Ri_inv, R_is);
//}
