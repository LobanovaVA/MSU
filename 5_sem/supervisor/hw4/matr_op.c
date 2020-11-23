#include "addition.h"

// for Problems 2-10
double
sum_Ax_b (double *A, double *X, double *B, int size)
{
  int i, k;
  double norm_Ax_B = 0, sum, elem_B;

  for (k = 0; k < size; k++)
    {
      sum = 0;
      elem_B = B[k];

      for (i = 0; i < size; i++)
        {
          sum += A[i * size + k] * X[i];
        }

      sum = fabs (sum - elem_B);
      norm_Ax_B += sum;
    }

  return norm_Ax_B;
}

double
sum_x_x0 (double *X, int size)
{
  int i;
  double norm = 0, elem;
  for (i = 0; i < size; i++)
    {
      elem = fabs (X[i] - (double) ((i + 1) & 1));
      norm += elem;
    }
  return norm;
}



// for Problems 1 3 4
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



// for Problems 2 3 4
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



// for Problems 5 6
void
AD_1x (double *A, double *X0, double *X, int size)
{
  int i, j;
  double sum, *pA = A;

  for (i = 0; i < size; i++)
    {
      sum = 0;
      for (j = 0; j < size; j++)
        {
          sum += pA[j] * X0[j];
          sum /= A[j * (size + 1)];
        }

      X[i] = sum;
      pA += size;
    }
}


// Probably may be used in 2 3
double
scalar_product (double *V, double *W, int size)
{
  int i;
  double ans = 0;

  for (i = 0; i < size; i++)
    ans += V[i] * W[i];

  return ans;
}
