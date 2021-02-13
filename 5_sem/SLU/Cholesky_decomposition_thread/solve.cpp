#include "solve.h"

/* ============ cholesky ============ */
bool
cholesky_symm_storage (int size, matr A, vect D, double norm)
{
  int i, j, k;
  double sum, r_ki, r_ii, d_k, inv_d_i_r_ii;
  double sum1, sum2, sum3, sum4, sum5;

  for (i = 0; i < size; i++)
    {
      sum = A[get_IND (i, i, size)];
      for (k = 0; k < i; k++)
        {
          r_ki = A[get_IND (k, i, size)];
          sum -= r_ki * r_ki * D[k];
        }

      if (is_small (sum, EPS * norm))
        return ERROR_EPS;

      D[i] = (sum < 0) ? -1 : 1;
      r_ii = sqrt (fabs (sum));

      inv_d_i_r_ii = D[i] / r_ii;
      A[get_IND (i, i, size)] = r_ii;

      for (j = i + 1; j < size - 3; j += 4)
        {
          sum1 = A[get_IND (i, j, size)];
          sum2 = A[get_IND (i, j + 1, size)];
          sum3 = A[get_IND (i, j + 2, size)];
          sum4 = A[get_IND (i, j + 3, size)];

          for (k = 0; k < i; k++)
            {
              d_k = D[k];
              sum1 -= A[get_IND (k, i, size)] * A[get_IND (k, j, size)] * d_k;
              sum2 -= A[get_IND (k, i, size)] * A[get_IND (k, j + 1, size)] * d_k;
              sum3 -= A[get_IND (k, i, size)] * A[get_IND (k, j + 2, size)] * d_k;
              sum4 -= A[get_IND (k, i, size)] * A[get_IND (k, j + 3, size)] * d_k;
            }

          A[get_IND (i, j, size)] = sum1 * inv_d_i_r_ii;
          A[get_IND (i, j + 1, size)] = sum2 * inv_d_i_r_ii;
          A[get_IND (i, j + 2, size)] = sum3 * inv_d_i_r_ii;
          A[get_IND (i, j + 3, size)] = sum4 * inv_d_i_r_ii;
        }

      for (; j < size; j += 1)
        {
          sum5 = A[get_IND (i, j, size)];
          for (k = 0; k < i; k++)
            {
              sum5 -= A[get_IND (k, i, size)] * A[get_IND (k, j, size)] * D[k];
            }

          A[get_IND (i, j, size)] = sum5 * inv_d_i_r_ii;
        }
    }
  return SUCCESS;
}


bool
cholesky (int size, int shift, matr A, vect D, double norm)
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
        {
          sum_ -= pA_k_i[0] * D[k] * pA_k_i[0];
        }

      if (is_small (sum_, EPS * norm))
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
            {
              sum[0] -= A[k * shift + i] * D[k] * A[k * shift + j];
            }

          pA_i_j[0] = sum[0] * inv_D_i_R_ii;
        }
    }
  return SUCCESS;
}


/* ========== thread solve ========== */
void
solve_thread (int matrix_size, int block_size, matr A, vect B, vect X, vect D, vect S,
              int th_p, int th_i, pthread_barrier_t *barrier, int *status)
{
  double norm = 0;

  norm = norm_A (matrix_size, A);
  if (th_i == MAIN_THREAD)
    printf("\nMatrix norm = %f\n", norm);

  cholesky_thread (matrix_size, block_size, A, D, norm,
                   th_p, th_i, barrier, status);

  /* no barrier used because all threads get ERROR_EPS */
  if (status[th_i] != SUCCESS)
    return;

  calc_y_thread (matrix_size, block_size, A, B, th_p, th_i, barrier);
  DB (matrix_size, block_size, D, B, th_p, th_i, barrier);
  calc_x_thread (matrix_size, block_size, A, B, S, th_p, th_i, barrier);

  if (th_i == MAIN_THREAD)
    memcpy (X, B, matrix_size * sizeof (double));

  pthread_barrier_wait (barrier);
}



void
cholesky_thread (int matrix_size, int block_size, matr A, vect D, double norm,
                 int th_p, int th_i, pthread_barrier_t *barrier, int *status)
{
  int squared_block_size = block_size * block_size;
  int num_blocks, mod, block_lim;
  int i, s;
  bool ret;

  std::unique_ptr <double []> ptr_R_bl, ptr_R_is,
      ptr_Ri_tmp, ptr_Ri_inv, ptr_D_bl, ptr_D_i, ptr_R_col;

  matr_bl R_bl, R_is, Ri_tmp, Ri_inv;
  vect_bl D_bl, D_i;
  column R_col;

  num_blocks = matrix_size / block_size;
  mod = matrix_size % block_size;
  block_lim = (mod) ? num_blocks + 1 : num_blocks;


  /* === memory allocation === */
  ptr_R_bl = std::make_unique <double []> (squared_block_size);
  ptr_R_is = std::make_unique <double []> (squared_block_size);
  ptr_Ri_tmp = std::make_unique <double []> (squared_block_size);
  ptr_Ri_inv = std::make_unique <double []> (squared_block_size);
  ptr_D_bl = std::make_unique <double []> (block_size);
  ptr_D_i = std::make_unique <double []> (block_size);
  ptr_R_col = std::make_unique <double []> (matrix_size * block_size);

  R_bl = ptr_R_bl.get ();
  R_is = ptr_R_is.get ();
  Ri_tmp = ptr_Ri_tmp.get ();
  Ri_inv = ptr_Ri_inv.get ();
  D_bl = ptr_D_bl.get ();
  D_i = ptr_D_i.get ();
  R_col = ptr_R_col.get ();


  /* === cholesky decoposition === */
  for (i = 0; i < block_lim; i++)
    {
      /* === get diag block R_{ii} and i-th column -> Ri_tmp, R_col === */
      pthread_barrier_wait (barrier);
      get_full_block (matrix_size, block_size, A, Ri_tmp, i, i, num_blocks, mod);
      get_column (matrix_size, block_size, A, R_col, i, num_blocks, mod);
      pthread_barrier_wait (barrier);

      /* === calculate diag block R_{ii} -> Ri_tmp, D_i === */
      ret = calc_diag_block_R (block_size, D, R_col, Ri_tmp, D_i,
                               norm, i, num_blocks, mod);
      if (ret)
        {
          /* no barrier used because all threads calculate R_{ii} and all get ERROR_EPS */
          status[th_i] = ERROR_EPS;
          return;
        }

      /* === put diag block R_{ii} and block D_{i} === */
      if (i % th_p == th_i)
        {
          put_diag_block (matrix_size, block_size, A, Ri_tmp, i, num_blocks, mod);
          put_vect_block (block_size, D, D_i, i, num_blocks, mod);
        }

      /* ===  not diag block R_{is} -> R_is === */
      if (i % th_p < th_i)
        s = i - (i % th_p) + th_i;
      else
        s = i - (i % th_p) + th_p + th_i;

      /* === inverse diag block R_{ii} -> Ri_inv === */
      if (s < block_lim)
        {
          ret = inverse_upper_matrix (block_size, block_size, Ri_tmp, Ri_inv, norm);
          if (ret)
            {
              /* no barrier used because all threads inverse R_{ii} and all get ERROR_EPS */
              status[th_i] = ERROR_EPS;
              return;
            }
        }

      for (; s < block_lim; s += th_p)
        {

          get_full_block (matrix_size, block_size, A, R_is, i, s, num_blocks, mod);
          calc_full_block_R (matrix_size, block_size, A, D, Ri_inv, D_i,
                             R_is, R_col, R_bl, D_bl, i, s, num_blocks, mod);
          put_full_block (matrix_size, block_size, A, R_is, i, s, num_blocks, mod);
        }
    }

  pthread_barrier_wait (barrier);
}


/* ============ calculate block R ============ */
bool
calc_diag_block_R (int block_size, vect D, column R_col, matr_bl Ri, vect_bl D_bl,
                   double norm, int i, int div, int mod)
{
  int j, shift = block_size * block_size;
  bool ret;
  matr_bl R_ji = R_col;

  for (j = 0 ; j < i; j++, R_ji += shift)
    {
      get_vect_block (block_size, D, D_bl, j, div, mod);
      A_minus_RtDR (block_size, Ri, R_ji, D_bl, R_ji);
    }

  if (i != div)
    ret = cholesky (block_size, block_size, Ri, D_bl, norm);
  else
    ret = cholesky (mod, block_size, Ri, D_bl, norm);

  if (ret)
    return ERROR_EPS;

  return SUCCESS;
}


void
calc_full_block_R (int matrix_size, int block_size, matr A, vect D,
                   matr_bl Ri_inv, vect_bl D_i, matr_bl R_is, column R_col,
                   matr_bl R_bl, vect_bl D_bl, int i, int s, int div, int mod)
{
  int j, shift = block_size * block_size;
  matr_bl R_ji = R_col;

  for (j = 0 ; j < i; j++, R_ji += shift)
    {
      get_full_block (matrix_size, block_size, A, R_bl, j, s, div, mod);
      get_vect_block (block_size, D, D_bl, j, div, mod);
      A_minus_RtDR (block_size, R_is, R_ji, D_bl, R_bl);
    }

  DRtA (block_size, D_i, Ri_inv, R_is);
}



/* ============ thread calculate solution ============ */
void
calc_y_thread (int matrix_size, int block_size, matr A, vect B,
               int th_p, int th_i, pthread_barrier_t *barrier)
{
  int squared_block_size = block_size * block_size;
  int num_blocks, mod, block_lim, column_lim = block_size;
  int i, s;

  std::unique_ptr <double []> ptr_R_bl, ptr_Ri_inv, ptr_B_i, ptr_B_s, ptr_B_diff;

  matr_bl R_bl, Ri_inv;
  vect_bl B_i, B_s, B_diff;

  num_blocks = matrix_size / block_size;
  mod = matrix_size % block_size;
  block_lim = (mod) ? num_blocks + 1 : num_blocks;


  /* === memory allocation === */
  ptr_R_bl = std::make_unique <double []> (squared_block_size);
  ptr_Ri_inv = std::make_unique <double []> (squared_block_size);
  ptr_B_i = std::make_unique <double []> (block_size);
  ptr_B_s = std::make_unique <double []> (block_size);
  ptr_B_diff = std::make_unique <double []> (block_size);

  R_bl = ptr_R_bl.get ();
  Ri_inv = ptr_Ri_inv.get ();
  B_i = ptr_B_i.get ();
  B_s = ptr_B_s.get ();
  B_diff = ptr_B_diff.get ();


  /* === calculate solution -> B === */
  for (i = 0; i < block_lim; i++)
    {
      if (i == num_blocks)
        column_lim = mod;

      /* === get diag block R_{ii} and block B_{i} -> Ri_bl, B_i=== */
      get_full_block (matrix_size, block_size, A, R_bl, i, i, num_blocks, mod);
      pthread_barrier_wait (barrier);
      get_vect_block (block_size, B, B_i, i, num_blocks, mod);
      pthread_barrier_wait (barrier);

      /* === inverse diag block R_{ii} -> Ri_inv === */
      if (i != num_blocks)
        inverse_upper_matrix (block_size, block_size, R_bl, Ri_inv, -1);
      else
        inverse_upper_matrix (column_lim, block_size, R_bl, Ri_inv, -1);

      /* === calculate inv_R_{ii}^T * B_{i} -> B_diff === */
      RtB (block_size, Ri_inv, B_i, B_diff);

      /* === change B_{s} -> B_s -> B === */
      if (i % th_p < th_i)
        s = i - (i % th_p) + th_i;
      else
        s = i - (i % th_p) + th_p + th_i;

      for (; s < block_lim; s += th_p)
        {
          get_full_block (matrix_size, block_size, A, R_bl, i, s, num_blocks, mod);
          get_vect_block (block_size, B, B_s, s, num_blocks, mod);

          /* === calculate B_{s} - R_{is}^T * (inv_R_{ii}^T * B_{i}) -> B_s === */
          Bs_MtB (block_size, B_s, R_bl, B_diff);

          put_vect_block (block_size, B, B_s, s, num_blocks, mod);
        }

      /* === put changed B_{i} -> B === */
      if (i % th_p == th_i)
        put_vect_block (block_size, B, B_diff, i, num_blocks, mod);
    }

  pthread_barrier_wait (barrier);
}



void
calc_x_thread (int matrix_size, int block_size, matr A, vect B, vect S,
                int th_p, int th_i, pthread_barrier_t *barrier)
{

  int squared_block_size = block_size * block_size;
  int num_blocks, mod, block_lim, column_lim;
  int i, s;

  std::unique_ptr <double []> ptr_R_bl, ptr_Ri_inv, ptr_B_bl, ptr_B_diff;

  matr_bl R_bl, Ri_inv;
  vect_bl B_bl, B_diff;

  num_blocks = matrix_size / block_size;
  mod = matrix_size % block_size;
  block_lim = (mod) ? num_blocks + 1 : num_blocks;


  /* === memory allocation === */
  ptr_R_bl = std::make_unique <double []> (squared_block_size);
  ptr_Ri_inv = std::make_unique <double []> (squared_block_size);
  ptr_B_bl = std::make_unique <double []> (block_size);
  ptr_B_diff = std::make_unique <double []> (block_size);

  R_bl = ptr_R_bl.get ();
  Ri_inv = ptr_Ri_inv.get ();
  B_bl = ptr_B_bl.get ();
  B_diff = ptr_B_diff.get ();


  /* === calculate solution -> B === */
  for (i = block_lim - 1; i >= 0; i--)
    {
      if (i == num_blocks)
        column_lim = mod;
      else
        column_lim = block_size;

      if (i % th_p < th_i)
        s = i - (i % th_p) + th_i;
      else
        s = i - (i % th_p) + th_p + th_i;

      /* === calculate diff for B_{i} from B_{s} === */
      bzero (B_diff, block_size * sizeof (double));
      for (; s < block_lim; s += th_p)
        {
          get_full_block (matrix_size, block_size, A, R_bl, i, s, num_blocks, mod);
          get_vect_block (block_size, B, B_bl, s, num_blocks, mod);
          Bdiff_MB (block_size, B_diff, R_bl, B_bl);
        }
      put_vect_block (block_size, S, B_diff, th_i, num_blocks, block_size);

      /* === calculate B_{i} -> B === */
      pthread_barrier_wait (barrier);
      if (i % th_p == th_i)
        {
          /* === inverse diag block R_{ii} -> Ri_inv === */
          get_full_block (matrix_size, block_size, A, R_bl, i, i, num_blocks, mod);
          inverse_upper_matrix (column_lim, block_size, R_bl, Ri_inv, -1);

          /* === calculate inv_R_{ii} * (B_{i} + B_diff) -> B === */
          get_vect_block (block_size, B, B_diff, i, num_blocks, mod);
          Bdiff_total (block_size, th_p, B_diff, S);
          RB (block_size, Ri_inv, B_diff, B_bl);
          put_vect_block (block_size, B, B_bl, i, num_blocks, mod);
        }
      pthread_barrier_wait (barrier);
    }

  pthread_barrier_wait (barrier);

}


void
DB (int matrix_size, int block_size, vect D, vect B,
    int th_p, int th_i, pthread_barrier_t *barrier)
{
  int j, k;

  for (k = th_i * block_size; k < matrix_size; k += th_p * block_size)
    {
      for (j = k; j < matrix_size && j < k + block_size; j++)
        B[j] *= D[j];
    }

  pthread_barrier_wait (barrier);
}
