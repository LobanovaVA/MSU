#include "matr_operation.h"

void
A_minus_RtDR (int size, matr A, matr R1, vect D, matr R2)
{
  int i, j, k;
  double sum;

  for (i = 0; i < size; i++)
    {
      for (j = 0; j < size; j++)
        {
          sum = 0;
          for (k = 0; k < size; k++)
            {
              sum += R1[k * size + i] * D[k] * R2[k * size + j];
            }
          A[i * size + j] -= sum;
        }
    }
}


void
DRtA (int size, vect D, matr R, matr A) // R_ii !
{
  int i, j, k;
  double sum;

  for (i = size - 1; i >= 0; i--)
    {
      for (j = 0; j < size; j ++)
        {
          sum = 0;
          for (k = 0; k <= i; k++)
            {
              sum += R[k * size + i] * A[k * size + j];
            }
          A[i * size + j] = D[i] * sum;
        }
    }
}


bool
reverse_upper_matrix (int size, matr R, matr E, double norm)
{

  int i, j, k;
  double r_ii, sum;

  for (i = size - 1; i >= 0; i--)
    {
      r_ii = R[i * size + i];
      if (is_small (r_ii, EPS * norm))
        return ERROR_EPS;

      r_ii = 1 / r_ii;
      E[i * size + i] = r_ii;

      for (j = i + 1; j < size; j++)
        {
          sum = 0;
          for (k = i + 1; k <= j; k++)
            {
              sum += R[i * size + k] * E[k * size + j];
            }
          E[i * size + j] = -sum * r_ii;
        }
    }
  return 0;
}




/*
bool
reverse_upper_matrix (int size, matr R, matr E, double norm)
{

  int i, j, k;
  double r_ii, sum1, sum2;

  for (i = size - 1; i >= 0; i--)
    {
      r_ii = R[i * size + i];
      if (is_small (r_ii, EPS * norm))
        return ERROR_EPS;

      r_ii = 1 / r_ii;
      E[i * size + i] = r_ii;

      for (j = i + 1; j < size - 1; j += 2)
        {
          sum1 = 0;
          sum2 = 0;
          for (k = i + 1; k <= j; k++)
            {
              sum1 += R[i * size + k] * E[k * size + j];
              sum2 += R[i * size + k] * E[k * size + j + 1];
            }

          sum2 += R[i * size + k] * E[k * size + j + 1];

          E[i * size + j] = -sum1 * r_ii;
          E[i * size + j + 1] = -sum2 * r_ii;
        }
      if (j == size - 1)
        {
          sum1 = 0;
          for (int k = i + 1; k <= j; k++)
            {
              sum1 += R[i * size + k] * E[k * size + j];
            }
          E[i * size + j] = -sum1 * r_ii;
          j++;
        }
    }
  return 0;
}

*/
