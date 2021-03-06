#include "matr_operation.h"

void
A_minus_RtDR_no_unroll (int size, matr A, matr R1, vect D, matr R2)
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
A_minus_RtDR (int size, matr A, matr R1, vect D, matr R2)
{
  int i, j, k;
  double sum[9];
  double D_k;
  double R1_k_i, R1_k_i_1, R1_k_i_2;
  double R2_k_j, R2_k_j_1, R2_k_j_2;
  matr pA_i_j, pR1_k_i, pR2_k_j;

  for (i = 0; i < size - 2; i += 3)
    {
      pA_i_j = &A[i * size];
      for (j = 0; j < size - 2; j += 3, pA_i_j += 3)
        {
          for (k = 0; k < 9; k++)
            sum[k] = 0;

          pR1_k_i = &R1[i];
          pR2_k_j = &R2[j];

          for (k = 0; k < size; k++)
            {
              D_k = D[k];

              R1_k_i = pR1_k_i[0];
              R1_k_i_1 = pR1_k_i[1];
              R1_k_i_2 = pR1_k_i[2];

              R2_k_j = pR2_k_j[0];
              R2_k_j_1 = pR2_k_j[1];
              R2_k_j_2 = pR2_k_j[2];

              sum[0] += R1_k_i * D_k * R2_k_j;
              sum[1] += R1_k_i * D_k * R2_k_j_1;
              sum[2] += R1_k_i * D_k * R2_k_j_2;

              sum[3] += R1_k_i_1 * D_k * R2_k_j;
              sum[4] += R1_k_i_1 * D_k * R2_k_j_1;
              sum[5] += R1_k_i_1 * D_k * R2_k_j_2;

              sum[6] += R1_k_i_2 * D_k * R2_k_j;
              sum[7] += R1_k_i_2 * D_k * R2_k_j_1;
              sum[8] += R1_k_i_2 * D_k * R2_k_j_2;

              pR1_k_i += size;
              pR2_k_j += size;
            }

          pA_i_j[0] -= sum[0];
          pA_i_j[1] -= sum[1];
          pA_i_j[2] -= sum[2];

          pA_i_j[size] -= sum[3];
          pA_i_j[size + 1] -= sum[4];
          pA_i_j[size + 2] -= sum[5];

          pA_i_j[2 * size] -= sum[6];
          pA_i_j[2 * size + 1] -= sum[7];
          pA_i_j[2 * size + 2] -= sum[8];
        }

      for (; j < size; j++)
        {
          for (k = 0; k < 9; k++)
            sum[k] = 0;

          pR1_k_i = &R1[i];
          pR2_k_j = &R2[j];

          for (k = 0; k < size; k++)
            {
              D_k = D[k];
              R2_k_j = pR2_k_j[0];

              sum[0] += pR1_k_i[0] * D_k * R2_k_j;
              sum[3] += pR1_k_i[1] * D_k * R2_k_j;
              sum[6] += pR1_k_i[2] * D_k * R2_k_j;

              pR1_k_i += size;
              pR2_k_j += size;
            }

          pA_i_j = &A[i * size + j];

          pA_i_j[0] -= sum[0];
          pA_i_j[size] -= sum[3];
          pA_i_j[2 * size] -= sum[6];
        }
    }

  for (; i < size; i++)
    {
      for (j = 0; j < size - 2; j += 3)
        {
          for (k = 0; k < 9; k++)
            sum[k] = 0;

          pR1_k_i = &R1[i];
          pR2_k_j = &R2[j];

          for (k = 0; k < size; k++)
            {
              D_k = D[k];
              R1_k_i = pR1_k_i[0];

              sum[0] += R1_k_i * D_k * pR2_k_j[0];
              sum[1] += R1_k_i * D_k * pR2_k_j[1];
              sum[2] += R1_k_i * D_k * pR2_k_j[2];

              pR1_k_i += size;
              pR2_k_j += size;
            }

          pA_i_j = &A[i * size + j];

          pA_i_j[0] -= sum[0];
          pA_i_j[1] -= sum[1];
          pA_i_j[2] -= sum[2];
        }

      for (; j < size; j++)
        {

          sum[0] = 0;

          for (k = 0; k < size; k++)
            {
              sum[0] += R1[k * size + i] * D[k] * R2[k * size + j];
            }

          A[i * size + j] -= sum[0];
        }
    }
}



void
DRtA (int size, vect D, matr R, matr A) // R_ii
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
inverse_upper_matrix (int size, matr R, matr E, double norm)
{

  int i, j, k;
  double r_ii, sum;

  //bzero (E, size * size * sizeof (double));
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

