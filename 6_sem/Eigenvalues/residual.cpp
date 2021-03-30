#include "residual.h"

/* ============ invariants ============ */
void
cacl_inv_symm_matr (int size, matr A, double &track, double &lenght, double norm)
{
  int i, j;
  double A_ii;
  track = lenght = 0;

  for (i = 0; i < size; i++)
    {
      A_ii = A[get_IND (i, i, size)];

      track += A_ii;
      lenght += A_ii * A_ii;

      for (j = i + 1; j < size; j++)
        lenght += 2 * A[get_IND (i, j, size)] * A[get_IND (i, j, size)];
    }

  track /= norm;
  lenght /= norm * norm;
}

void
cacl_inv_tridiag_matr (int size, matr A, double &track, double &lenght, double norm)
{
  int i;
  double A_ii;
  track = lenght = 0;

  for (i = 0; i < size; i++)
    {
      A_ii = A[get_IND (i, i, size)];

      track += A_ii;
      lenght += A_ii * A_ii;

      if (i + 1 < size)
        lenght += 2 * A[get_IND (i, i + 1, size)] * A[get_IND (i, i + 1, size)];
    }

  track /= norm;
  lenght /= norm * norm;
}

void
cacl_inv_diag_matr (int size, vect V, double &track, double &lenght, double norm)
{
  int i;
  double elem;
  track = lenght = 0;

  for (i = 0; i < size; i++)
    {
      elem = V[i];

      track += elem;
      lenght += elem * elem;
    }

  track /= norm;
  lenght /= norm * norm;
}



/* ============ norm ============ */
double
norm_symm_matr (int size, matr A)
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
norm_tridiag_matr (int size, matr A)
{
  int i, j;
  double norm = 0, sum;

  /* 1-st string */
  sum = fabs (A[0]) + fabs (A[1]);
  if (sum > norm)
    norm = sum;

  /* last string */
  sum = fabs (A[get_IND (size - 1, size - 2, size)]) + fabs (A[get_IND (size - 1, size - 1, size)]);
  if (sum > norm)
    norm = sum;

  /* others strings */
  for (i = 1; i < size - 1; i++)
    {
      sum = 0;
      for (j = i - 1; j <= i + 1; j++)
        {
          sum += fabs (A[get_IND (i, j, size)]);
        }

      if (sum > norm)
        norm = sum;
    }

  return norm;
}
