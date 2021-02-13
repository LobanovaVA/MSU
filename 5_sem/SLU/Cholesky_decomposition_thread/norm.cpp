#include "norm.h"

double
norm_A (int size, matr A)
{
  int i, j;
  double norm = 0, sum;

  for (i = 0; i < size; i++)
    {
      sum = 0;
      for (j = 0; j < size; j++)
        {
          sum += fabs (A[get_IND (i, j, size)]);
        }

      if (sum > norm)
        norm = sum;
    }
  return norm;
}

double
norm_Ax_b (int size, matr A, vect B, vect X)
{
  int i, k;
  double norm_B = 0, norm_Ax_B = 0, sum, elem_B;

  for (k = 0; k < size; k++)
    {
      sum = 0;
      elem_B = B[k];

      for (i = 0; i < size; i++)
        {
          sum += A[get_IND (i, k, size)] * X[i];
        }

      sum = fabs (sum - elem_B);
      if (sum > norm_Ax_B)
        norm_Ax_B = sum;

      elem_B = fabs (elem_B);
      if (elem_B > norm_B)
        norm_B = elem_B;
    }
  return norm_Ax_B / norm_B;
}

double
norm_x_x0 (int matrix_size, vect X)
{
  int i;
  double norm = 0, elem;
  for (i = 0; i < matrix_size; i++)
    {
      elem = fabs (X[i] - (double) ((i + 1) & 1));
      if (elem > norm)
        norm = elem;
    }
  return norm;
}


void
norm_Ax_b_thread (int size, matr A, vect B, vect X,
                  int th_p, int th_i, pthread_barrier_t *barrier, double &residual)
{
  int i, k;
  double norm_B = 0, norm_Ax_B = 0, sum, elem_B;

  (void) th_p;
  if (th_i == MAIN_THREAD)
    {
      for (k = 0; k < size; k++)
        {
          sum = 0;
          elem_B = B[k];

          for (i = 0; i < size; i++)
            {
              sum += A[get_IND (i, k, size)] * X[i];
            }

          sum = fabs (sum - elem_B);
          if (sum > norm_Ax_B)
            norm_Ax_B = sum;

          elem_B = fabs (elem_B);
          if (elem_B > norm_B)
            norm_B = elem_B;
        }

      residual = norm_Ax_B / norm_B;
    }

  pthread_barrier_wait (barrier);
}
