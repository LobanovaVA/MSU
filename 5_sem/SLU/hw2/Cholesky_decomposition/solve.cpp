#include "solve.h"

int
solve (int matrix_size, int block_size, matr A, vect B, vect D,
       vect X, matr R1, matr R2, matr A_bl, vect D_bl)
{
  bool ret;
  double norm;

  norm = norm_A (matrix_size, A);
  printf("\nMatrix norm = %lf\n", norm);

  ret = cholesky_block (matrix_size, block_size, A, D, R1, R2, A_bl, D_bl, norm);
  if (ret)
    return ERROR_SINGULAR_MATRIX_R;

  ret = culc_y_not_block (matrix_size, A, B, norm);
  if (ret)
    return ERROR_CALC_Y;
  //printf("\nY\n"); print_matrix (B, matrix_size, 1, matrix_size);

  ret = culc_x_not_block (matrix_size, A, D, B, norm);
  if (ret)
    return ERROR_CALC_X;
  //printf("\nX\n"); print_matrix (B, matrix_size, 1, matrix_size);

  memcpy (X, B, matrix_size * sizeof (double));
  //printf("\nX\n"); print_matrix (X, matrix_size, 1, matrix_size);

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

      D[i] = (sum < 0) ? -1 : 1;
      if (is_small (A[get_IND (i, i, size)], EPS * norm))
        return ERROR_EPS;

      r_ii = sqrt (fabs (sum));
      if (is_small (r_ii, EPS * norm))
        return ERROR_EPS;

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
cholesky_not_symm_storage (int size, int shift, matr A, vect D, double norm)
{
  int i, j, k;
  double sum, r_ki, r_ii, d_k, inv_d_i_r_ii;
  double sum1, sum2, sum3, sum4, sum5;

  for (i = 0; i < size; i++)
    {
      sum = A[i * shift + i];
      for (k = 0; k < i; k++)
        {
          r_ki = A[k * shift + i];
          sum -= r_ki * r_ki * D[k];
        }

      D[i] = (sum > 0) ? 1 : -1;
      if (is_small (A[i * shift + i], EPS * norm)) //можно убрать
        return ERROR_EPS;

      r_ii = sqrt (fabs (sum));
      if (is_small (r_ii, EPS * norm))
        return ERROR_EPS;

      inv_d_i_r_ii = D[i] / r_ii;
      A[i * shift + i] = r_ii;

      for (j = i + 1; j < size - 3; j += 4)
        {
          sum1 = A[i * shift + j];
          sum2 = A[i * shift + j + 1];
          sum3 = A[i * shift + j + 2];
          sum4 = A[i * shift + j + 3];

          for (k = 0; k < i; k++)
            {
              d_k = D[k];
              sum1 -= A[k * shift + i] * A[k * shift + j] * d_k;
              sum2 -= A[k * shift + i] * A[k * shift + j + 1] * d_k;
              sum3 -= A[k * shift + i] * A[k * shift + j + 2] * d_k;
              sum4 -= A[k * shift + i] * A[k * shift + j + 3] * d_k;
            }

          A[i * shift + j] = sum1 * inv_d_i_r_ii;
          A[i * shift + j + 1] = sum2 * inv_d_i_r_ii;
          A[i * shift + j + 2] = sum3 * inv_d_i_r_ii;
          A[i * shift + j + 3] = sum4 * inv_d_i_r_ii;
        }

      for (; j < size; j += 1)
        {
          sum5 = A[i * shift + j];
          for (k = 0; k < i; k++)
            {
              sum5 -= A[k * shift + i] * A[k * shift + j] * D[k];
            }

          A[i * shift + j] = sum5 * inv_d_i_r_ii;
        }
    }
  return 0;
}

bool
cholesky_block (int matrix_size, int block_size, matr A, vect D,
                matr R1, matr R2, matr A_bl, vect D_bl, double norm)
{
  int num_blocks, mod, block_lim, i, s;
  bool ret;

  num_blocks = matrix_size / block_size;
  mod = matrix_size % block_size;
  block_lim = (mod) ? num_blocks + 1 : num_blocks;

  for (i = 0; i < block_lim; i++)
    {
      ret = culc_diag_block_R (matrix_size, block_size, A, D, R1, R2,
                               A_bl, D_bl, norm, i, num_blocks, mod);
      if (ret)
        return ERROR_EPS;

      for (s = i + 1; s < block_lim; s++)
        {
          ret = culc_full_block_R (matrix_size, block_size, A, D, R1, R2,
                                   A_bl, D_bl, norm, i, s, num_blocks, mod);
          if (ret)
            return ERROR_EPS;
        }
    }
  if (is_small (A[get_IND (matrix_size - 1, matrix_size - 1, matrix_size)], norm * (10e-9)))
    return ERROR_EPS;

  return 0;
}


// ====== culculate block R ======
bool
culc_diag_block_R (int matrix_size, int block_size, matr A, vect D, matr R1, matr R2,
                   matr A_bl, vect D_bl, double norm, int i, int div, int mod)
{
  int j;
  bool ret;
  get_full_block (matrix_size, block_size, A, A_bl, i, i, div, mod);

  for (j = 0 ; j < i; j++)
    {
      get_full_block (matrix_size, block_size, A, R1, j, i, div, mod);
      get_full_block (matrix_size, block_size, A, R2, j, i, div, mod);
      get_vect_block (block_size, D, D_bl, j, div, mod);

      A_minus_RtDR (block_size, A_bl, R1, D_bl, R2); //тут можно передеавать R1 и R1
    }

  if (i != div)
    ret = cholesky_not_symm_storage (block_size, block_size, A_bl, D_bl, norm);
  else
    ret = cholesky_not_symm_storage (mod, block_size, A_bl, D_bl, norm);

  if (ret)
    return ERROR_EPS;

  put_diag_block (matrix_size, block_size, A, A_bl, i, div, mod); // it's R_ii
  put_vect_block (block_size, D, D_bl, i, div, mod);

  return 0;
}

bool
culc_full_block_R (int matrix_size, int block_size, matr A, vect D, matr R1, matr R2,
                   matr A_bl, vect D_bl, double norm, int i, int s, int div, int mod)
{
  int j;
  bool ret;

  get_full_block (matrix_size, block_size, A, A_bl, i, s, div, mod);

  for (j = 0 ; j < i; j++)
    {
      get_full_block (matrix_size, block_size, A, R1, j, i, div, mod);
      get_full_block (matrix_size, block_size, A, R2, j, s, div, mod);
      get_vect_block (block_size, D, D_bl, j, div, mod);
      A_minus_RtDR (block_size, A_bl, R1, D_bl, R2);
    }

  get_diag_block (matrix_size, block_size, A, R1, i, div, mod);

  ret = reverse_upper_matrix  (block_size, R1, R2, norm);
  if (ret)
    return ERROR_EPS;

  get_vect_block (block_size, D, D_bl, i, div, mod);
  DRtA (block_size, D_bl, R2, A_bl);
  put_full_block (matrix_size, block_size, A, A_bl, i, s, div, mod);
  return 0;
}


// ====== culculate solution ======
bool
culc_y_not_block (int matrix_size, matr A, vect B, double norm)
{
  int i, j;
  double sum;
  if (!norm) return 0;

  for (j = 0; j < matrix_size; j++)
    {
      sum = 0;
      for (i = 0; i < j; i++)
        {
          sum += B [i] * A[get_IND(i, j, matrix_size)];
        }
      B[j] = (B [j] - sum) / A[get_IND(j, j, matrix_size)];
    }
  return 0;
}


bool
culc_x_not_block (int matrix_size, matr A, vect D, vect B, double norm)
{
  int i, j;
  double sum;
  if (!norm) return 0;

  for (i = matrix_size - 1; i >= 0; i--)
    {
      sum = 0;
      for (j = matrix_size - 1; j > i; j--)
        {
          sum += B[j] * A[get_IND(i, j, matrix_size)];
        }
      B[i] = D[i] * (B [i] - sum * D[i]) / A[get_IND(i, i, matrix_size)];
    }
  return 0;
}


/*
bool
culc_y_not_block (int matrix_size, matr A, vect B, double norm)
{
  int i, j;
  double r_jj, elem_B;

  for (j = 0; j < matrix_size; j++)
    {
      r_jj = A[get_IND(j, j, matrix_size)];
      if (is_small (r_jj, EPS * norm))
        return ERROR_EPS;

      B[j] /= r_jj;
      elem_B = B[j];

      for (i = j + 1; i < matrix_size; i++)
        {
          B[i] -= elem_B * A[get_IND(j, i, matrix_size)];
        }
    }
  return 0;
}



bool
culc_x_not_block (int matrix_size, matr A, vect D, vect B, double norm)
{
  int i, j;
  double r_jj, elem_B;

  // (DR)_ij = d_i * r_ij
  for (j = matrix_size - 1; j >= 0; j--)
    {
      r_jj = D[j] * A[get_IND(j, j, matrix_size)];
      if (is_small (r_jj, EPS * norm))
        return ERROR_EPS;

      B[j] /= r_jj;
      elem_B = B[j];

      for (i = j - 1; i >= 0; i--)
        {
          B[i] -= elem_B * D[i] * A[get_IND(i, j, matrix_size)];
        }
    }
  return 0;
}
*/


/*
bool
block_culc_y (int size, matr R, vect B, double norm)
{
  int i, j;
  double r_jj, elem_B;

  for (j = size - 1; j >= 0; j--)
    {
      r_jj = R[j * (size + 1)];
      if (is_small (r_jj, EPS * norm))
        return ERROR_SINGULAR_MATRIX;

      B[size - j] /= r_jj;
      elem_B = B[size - j];

      for (i = j - 1; i >= 0; i--)
        {
          B[size - i] -= elem_B * R[i * size + j];
        }
    }
  return 0;
}
*/
/*
bool
culc_y (int matrix_size, int block_size, matr A, matr R, vect B, vect B_bl, double norm)
{
  int num_blocks, block_lim, i, j, s;
  bool ret;

  num_blocks = matrix_size / block_size;
  block_lim = (matrix_size % block_size) ? num_blocks + 1 : num_blocks;

  for (i = 0; i < block_lim; i++)
    {
      get_block_D (matrix_size, block_size, B, B_bl, i);
      for (j = 0; j < block_lim; j++)
        {
          get_block (matrix_size, block_size, A, R1, j, i);

        }


    }
}
*/
