#include "addition.h"

// Problem 1
double
problem_1 (double *A, double *X0, double *X, int m, int n)
{
  int i;
  double *ptr, tmp, sc_1 = 0, sc_2 = 0;

  for (i = 0; i <= m; i++) /* x_m -> X0, Ax_m -> X */
    {
      Ax(A, X0, X, n);
      ptr = X0;
      X0 = X;
      X = ptr;
    }

  for (i = 0; i < n; i++)  /* <Ax_m, x_m> и <x_m, x_m> */
    {
      tmp = X[i];
      sc_1 += X0[i] * tmp;
      sc_2 += tmp * tmp;
    }

  if (!(sc_2 < 0 || sc_2 > 0))
    {
      printf ("\nERROR: Scalar product <x_m, x_m> = 0\n");
      return ERROR_SCALAR_PRODUCT;
    }

  if (!(m & 1))
    for (i = 0; i < n; i++)
      X0[i] = X[i];

  return sc_1 / sc_2;
}



// Problem 2
void
problem_2 (double *A, double *X0, double *X, double *B, double t, int m, int n)
{
  int i, j;

  for (i = 0; i < m; i++)
    {
      b_Ax (A, X0, X, B, n);  /* b - Ax_k -> X */

      for (j = 0; j < n; j++) /* x_k + t [b - Ax_k] -> X0 */
        X0[j] += t * X[j];
    }

  for (i = 0; i < n; i++)
    X[i] = X0[i];
}



// Problem 3
void
problem_3 (double *A, double *X0, double *X, double *B, double *R, int m, int n)
{
  int i, j;
  double t, tmp, sc_1, sc_2;

  for (i = 0; i < m; i++)
    {
      b_Ax (A, X0, X, B, n); /* -r_k = b - Ax_k -> Х */
      Ax (A, X, R, n);			 /* Ar_k -> R */


      sc_1=0; sc_2=0;
      for (j = 0; j < n; j++) /* <r_k, r_k> и <Ar_k, r_k> */
        {
          tmp = X[i];
          sc_1 += tmp * tmp;
          sc_2 += R[i] * tmp;
        }

      if (!(sc_2 < 0 || sc_2 > 0))
        {
          printf ("\nERROR: Scalar product <Ar_k, r_k> = 0\n");
          return ;
        }

      t = sc_1 / sc_2;

//      if (!(t < 0 || t > 0))
//        {
//          printf ("t = <r_k, r_k> / <Ar_k, r_k> = 0\n");
//          return;
//        }

      for (j = 0; j < n; j++) /* x_k + t [b - Ax_k] -> X0 */
        X0[j] += t * X[j];
    }

  for (i = 0; i < n; i++)
    X[i] = X0[i];
}
