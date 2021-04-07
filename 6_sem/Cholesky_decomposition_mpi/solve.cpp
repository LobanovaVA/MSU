#include "solve.h"
#include "norm.h"
#include "block_action.h"
#include "matr_operation.h"

#include "in_out.h"

int
MPI_solve (size_arguments &size_args, matr *ptr_columns, vect D, vect B, vect Y)
{
  int err = NO_ERROR;
  double norm;

  std::unique_ptr <double []> ptr_diag_inv;
  ptr_diag_inv = std::make_unique <double []> (size_args.block_lim * size_args.squared_block_size);
  buff_ptr diag_inv = ptr_diag_inv.get ();

  norm = MPI_norm_A (size_args, ptr_columns);
  printf_main_process ("\nMatrix norm = %10.3e\n", norm);
  norm = (norm < 100) ? norm : 1;

  err = MPI_cholesky (size_args, ptr_columns, D, diag_inv, norm * EPS);
  if (err != NO_ERROR)
    return err;

  MPI_calc_y (size_args, ptr_columns, B, Y, diag_inv); // answer -> Y
  DB (size_args.matrix_size, D, Y);
  MPI_calc_x (size_args, ptr_columns, Y, B); // answer -> B
  if (size_args.my_rank == MAIN_PROCESS)
    memcpy (Y, B, size_args.matrix_size * sizeof (double));

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
  matr_bl orig_R_i = R_col + ind_bl * size_args.squared_block_size;

  int col_width = size_args.get_col_width(ind_bl);

  for (int j_bl = 0 ; j_bl < ind_bl; j_bl++)
    {
      A_minus_RtDR (col_width, size_args.block_size, orig_R_i, R_ji, D_j, R_ji);
      R_ji += size_args.squared_block_size;
      D_j += size_args.block_size;
    }

  return cholesky (col_width , size_args.block_size, orig_R_i, D_j, eps);;
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
      A_minus_RtDR (size_args.block_size, size_args.block_size, R_is, R_ji, D_j, R_js);
      R_ji += size_args.squared_block_size;
      D_j += size_args.block_size;
    }

  DRtA (size_args.block_size, D_j, Ri_inv, R_is);
  put_full_block (i_bl, s_bl, size_args, ptr_columns, R_is);
}//TODO for last block other func without get/put block


// ======================================= calculate solution ======================================= //
#if 0 //old
void
MPI_calc_y (size_arguments &size_args, matr *ptr_columns, vect B, vect Y, buff_ptr diag_inv)
{
  int col_width;
  vect_bl B_i = B, Y_j, Y_i = Y;
  matr_bl R_ji = nullptr, Ri_inv = diag_inv;

  for (int i_bl = 0; i_bl < size_args.block_lim; i_bl++,
       B_i += size_args.block_size, Y_i += size_args.block_size,
       Ri_inv += size_args.squared_block_size)
    {
      col_width = size_args.get_col_width (i_bl);
      if (size_args.is_my_column (i_bl))
        {
          Y_j = Y;
          R_ji = ptr_columns [size_args.get_local_bl_ind (i_bl)];

          for (int j_bl = 0; j_bl < i_bl; j_bl++,
               Y_j += size_args.block_size,
               R_ji += col_width * size_args.block_size)
            B_minus_RtY (col_width, size_args.block_size, B_i, R_ji, Y_j);

          RtB (col_width, Ri_inv, B_i, Y_i);
        }

      MPI_Bcast (Y_i, col_width, MPI_DOUBLE,
                 size_args.get_column_owner (i_bl), MPI_COMM_WORLD);
    }
}
#endif

void
MPI_calc_y (size_arguments &size_args, matr *ptr_columns, vect B, vect Y, buff_ptr diag_inv)
{
  vect_bl B_i = B, B_s, Y_i = Y;
  matr_bl R_is = nullptr, Ri_inv = diag_inv;

  for (int i_bl = 0; i_bl < size_args.block_lim; i_bl++,
       B_i += size_args.block_size, Y_i += size_args.block_size,
       Ri_inv += size_args.squared_block_size)
    {
      // === calc Y_i and send === //
      if (size_args.is_my_column (i_bl))
        RtB (size_args.get_col_width (i_bl), Ri_inv, B_i, Y_i);

      MPI_Bcast (Y_i, size_args.get_col_width (i_bl), MPI_DOUBLE,
                 size_args.get_column_owner (i_bl), MPI_COMM_WORLD);

      // === use new Y_i for all sum components === //
      int s_bl = size_args.get_start_ind (i_bl);
      B_s = B + s_bl * size_args.block_size;

      for (; s_bl < size_args.block_lim; s_bl += size_args.comm_size,
           B_s += size_args.block_size * size_args.comm_size)
        // comm_size is global shift in 1 proccess
        {
          R_is = ptr_columns [size_args.get_local_bl_ind (s_bl)];
          R_is += i_bl * size_args.get_col_width (s_bl) * size_args.block_size;
          B_minus_RtY (size_args.get_col_width (s_bl), size_args.block_size, B_s, R_is, Y_i);
        }
    }
}


void
MPI_calc_x (size_arguments &size_args, matr *ptr_columns, vect B, vect X)
{
  double sum;
  std::unique_ptr <double []> ptr_elem_row;
  vect elem_row = nullptr;

  if (size_args.my_rank == MAIN_PROCESS)
    {
      ptr_elem_row = std::make_unique <double []> (size_args.matrix_size);
      elem_row = ptr_elem_row.get ();
    }

  for (int i = size_args.matrix_size - 1; i >= 0; i--)
    {
      MPI_action_elem_row (i, size_args, ptr_columns, elem_row, GATHER);

      if (size_args.my_rank == MAIN_PROCESS)
        {
          sum = 0;
          for (int j = i + 1; j < size_args.matrix_size; j++)
            sum += elem_row[j] * X[j];

          X[i] = (B[i] - sum) / elem_row[i];
        }
    }
}


void
DB (int size, vect D, vect B)
{
  for (int i = 0; i < size; i++)
    B[i] *= D[i];
}
