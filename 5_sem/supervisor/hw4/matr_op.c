#include "addition.h"

void
Ax (double *A, double *X0, double *X, int size)
{
  int i, j;
  double sum, *pA = A;

  for (i = 0; i < size; i++)
    {
      sum = 0;
      for (j = 0; j < size; j++)
        sum += pA[j] * X0[j];

      X[i] = sum;
      pA += size;
    }
}


void
b_Ax (double *A, double *X0, double *X, double *B, int size)
{
  int i, j;
  double sum, *pA = A;
  for (i = 0; i < size; i++)
    {
      sum = 0;
      for (j = 0; j < size; j++)
        sum += pA[j] * X0[j];

      X[i] = B[i] - sum;
      pA += size;
    }
}


double
scalar_product (double *V, double *W, int size)
{
  int i;
  double ans = 0;

  for (i = 0; i < size; i++)
    ans += V[i] * W[i];

  return ans;
}
