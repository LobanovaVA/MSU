#include "matr_operation"

void minus_RtDR (int size, matr A, matr R1, vect D, matr R2)
{
  int i, j, k;
  double sum1, sum2, sum3, sum4, sum5;
  double d_k, r1_ki;

  for (i = 0; i < size; i++)
    {
      for (j = 0; j < size - 3; j += 4)
        {
          sum1 = sum2 = sum3 = sum4 = 0;
          for (k = 0; k < size; k++)
            {
              d_k = D[k];
              r1_ki = R1[k * size + i];
              sum1 += r1_ki * R2[k * size + j] * d_k;
              sum2 += r1_ki * R2[k * size + j + 1] * d_k;
              sum3 += r1_ki * R2[k * size + j + 2] * d_k;
              sum4 += r1_ki * R2[k * size + j + 3] * d_k;
            }

          A[i * size + j] -= sum1;
          A[i * size + j + 1] -= sum2;
          A[i * size + j + 2] -= sum3;
          A[i * size + j + 3] -= sum4;
        }
      for (; j < size; j++)
        {
          sum5 = 0;
          for (k = 0; k < size; k++)
            {
              sum5 += R1[k * size + i] * R2[k * size + j] * D[k];
            }
          A[i * size + j] -= sum5;
        }
    }
}


void
DRtA (int size, matr A, matr R, vect D)
{
  int i, j, k;
  double sum[4], r_ki, d_i;

  for (i = size - 1; i >= 0; i--)
    {
      for (j = 0; j < size - 3; j += 4)
        {
          bzero (sum, 4 * sizeof (double));
          for (k = 0; k <= i; k++)
            {
              r_ki = R[k * size + i];
              sum[0] += r_ki * A[k * size + j];
              sum[1] += r_ki * A[k * size + j + 1];
              sum[2] += r_ki * A[k * size + j + 2];
              sum[3] += r_ki * A[k * size + j + 3];
            }

          d_i = D[i];
          A[i * size + j] = sum[0] * d_i;
          A[i * size + j + 1] = sum[1] * d_i;
          A[i * size + j + 2] = sum[2] * d_i;
          A[i * size + j + 3] = sum[3] * d_i;
        }

      for (; j < size - 1; j += 1)
        {
          bzero (sum, 4 * sizeof (double));
          for (k = 0; k <= i; k++)
            {
              sum[0] += R[k * size + i] * A[k * size + j];
            }
          A[i * size + j] = sum[0] * D[i];
        }
    }
}




bool
reverse_upper (int size, matr R, matr E, double norm)
{
  int i, j;
  double r_jj;

  bzero (E, size * size * sizeof (double));
  for (i = j = 0; i < size; i++, j += size)
    E [j] = 1;

  for (j = size - 1; j >= 0; j--)
    {
      r_jj = R[j * (size + 1)];
      if (is_small (r_jj, EPS * norm))
        return ERROR_SINGULAR_MATRIX;

      r_jj = 1 / r_jj;
      E[j * (size + 1)] = r_jj;

      for (i = j - 1; i >= 0; i--)
        {
          E[i * size + j] -= r_jj * R[i * size + j];
        }
    }
  return 0;
}





