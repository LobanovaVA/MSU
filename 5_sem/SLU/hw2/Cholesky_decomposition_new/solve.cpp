#include "solve.h"

int
solve (int matrix_size, int block_size, matr A, vect B, vect D,
       vect X, matr R1, matr R2, matr Ri, matr A_bl, vect D_bl)
{
  bool ret;
  double norm;

  norm = norm_A (matrix_size, A);
  printf("\nMatrix norm = %lf\n", norm);

  ret = cholesky_block (matrix_size, block_size, A, D, R1, R2, Ri, A_bl, D_bl, norm);
  if (ret)
    return ERROR_SINGULAR_MATRIX_R;

  culc_y_not_block (matrix_size, A, B);
  culc_x_not_block (matrix_size, A, D, B);

  memcpy (X, B, matrix_size * sizeof (double));
  return 0;
}


// ====== cholesky ======
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
  return 0;
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
  return 0;
}


bool
cholesky_block (int matrix_size, int block_size, matr A, vect D,
                matr R1, matr R2, matr Ri, matr A_bl, vect D_bl, double norm)
{
  int num_blocks, mod, block_lim, i, s;
  bool ret;

  num_blocks = matrix_size / block_size;
  mod = matrix_size % block_size;
  block_lim = (mod) ? num_blocks + 1 : num_blocks;

  for (i = 0; i < block_lim; i++)
    {
      ret = culc_diag_block_R (matrix_size, block_size, A, D, R1, Ri,
                               A_bl, D_bl, norm, i, num_blocks, mod);
      if (ret)
        return ERROR_EPS;

      for (s = i + 1; s < block_lim; s++)
        {
          ret = culc_full_block_R (matrix_size, block_size, A, D, R1, R2, Ri,
                                   A_bl, D_bl, i, s, num_blocks, mod);
          if (ret)
            return ERROR_EPS;
        }
    }

  return 0;
}


// ====== culculate block R ======
bool
culc_diag_block_R (int matrix_size, int block_size, matr A, vect D, matr R1, matr Ri,
                   matr A_bl, vect D_bl, double norm, int i, int div, int mod)
{
  int j;
  bool ret;
  get_full_block (matrix_size, block_size, A, A_bl, i, i, div, mod);

  for (j = 0 ; j < i; j++)
    {
      get_full_block (matrix_size, block_size, A, R1, j, i, div, mod);
      get_vect_block (block_size, D, D_bl, j, div, mod);
      A_minus_RtDR (block_size, A_bl, R1, D_bl, R1);
    }

  if (i != div)
    ret = cholesky (block_size, block_size, A_bl, D_bl, norm);
  else
    ret = cholesky (mod, block_size, A_bl, D_bl, norm);

  if (ret)
    return ERROR_EPS;

  put_diag_block (matrix_size, block_size, A, A_bl, i, div, mod);
  put_vect_block (block_size, D, D_bl, i, div, mod);

  /* inverse R_ii */
  if (i != div)
    {
      ret = reverse_upper_matrix (block_size, A_bl, Ri, norm);
      if (ret)
        return ERROR_EPS;
    }

  return 0;
}


bool
culc_full_block_R (int matrix_size, int block_size, matr A, vect D, matr R1, matr R2,
                   matr Ri, matr A_bl, vect D_bl, int i, int s, int div, int mod)
{
  int j;

  get_full_block (matrix_size, block_size, A, A_bl, i, s, div, mod);

  for (j = 0 ; j < i; j++)
    {
      get_full_block (matrix_size, block_size, A, R1, j, i, div, mod);
      get_full_block (matrix_size, block_size, A, R2, j, s, div, mod);
      get_vect_block (block_size, D, D_bl, j, div, mod);
      A_minus_RtDR (block_size, A_bl, R1, D_bl, R2);
    }

  get_vect_block (block_size, D, D_bl, i, div, mod);
  DRtA (block_size, D_bl, Ri, A_bl);
  put_full_block (matrix_size, block_size, A, A_bl, i, s, div, mod);

  return 0;
}



// ====== culculate solution ======
void
culc_y_not_block (int matrix_size, matr A, vect B)
{
  int i, j;
  double sum;

  for (j = 0; j < matrix_size; j++)
    {
      sum = 0;
      for (i = 0; i < j; i++)
        {
          sum += B[i] * A[get_IND(i, j, matrix_size)];
        }
      B[j] = (B[j] - sum) / A[get_IND(j, j, matrix_size)];
    }
}


void
culc_x_not_block (int matrix_size, matr A, vect D, vect B)
{
  int i, j;
  double sum;

  for (i = matrix_size - 1; i >= 0; i--)
    {
      sum = 0;
      for (j = matrix_size - 1; j > i; j--)
        {
          sum += B[j] * A[get_IND(i, j, matrix_size)];
        }
      B[i] = D[i] * (B[i] - sum * D[i]) / A[get_IND(i, i, matrix_size)];
    }
}

