#include "addition.h"

// Problem 1
double
problem_1 (double *A, double *X0, double *X, int m, int n)
{
  int i;
  double *ptr, tmp, sc_1 = 0, sc_2 = 0;

  for (i = 0; i <= m; i++) /* x_m -> X0, Ax_m -> X */
    {
      Ax (A, X0, X, n);
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
      Ax_b (A, X0, X, B, n); /* Ax_k - b -> X */

      for (j = 0; j < n; j++)
        X0[j] -= t * X[j]; /* x_k - t [Ax_k - b] -> X0 */
    }

  for (i = 0; i < n; i++)
    X[i] = X0[i];
}




// for Problem 3, 4, 6
void
problem_34 (double *A, double *X0, double *X, double *B, double *R, int m, int n,
            void (*culc_Tk) (double *, double *, int, double *, double *))
{
  int i, j;
  double t, sc_1, sc_2;

  Ax_b (A, X0, R, B, n); /* r_0 = Ax_0 - b -> R */

  for (i = 0; i < m; i++)
    {
      Ax (A, R, X, n); /* Ar_k -> X */

      sc_1 = 0;
      sc_2 = 0;
      culc_Tk (R, X, n, &sc_1, &sc_2);

      if (!(sc_2 < 0 || sc_2 > 0))
        {
          printf ("\nERROR: Scalar product = 0\n");
          return;
        }

      t = sc_1 / sc_2;

      if (!(t < 0 || t > 0))
        {
          printf ("\nERROR: Inv scalar product = 0\n");
          return;
        }

      for (j = 0; j < n; j++)
        {
          X0[j] -= t * R[j]; /* x_k+1 = x_k - t_k [r_k] -> X0 */
          R[j] -= t * X[j];  /* r_k+1 = r_k - t_k [Ar_k] -> R */
        }
    }

  for (i = 0; i < n; i++)
    X[i] = X0[i];
}


// for Problem 3
void
culc_Tk_3 (double *R, double *X, int n, double *ans_1, double *ans_2)
{
  int j;
  double sc_1 = 0, sc_2 = 0, tmp;

  /* R = r_k X = Ar_k and sc_1 = <R, R> sc_2 = <X, R> */
  for (j = 0; j < n; j++)
    {
      tmp = R[j];
      sc_1 += tmp * tmp;
      sc_2 += X[j] * tmp;
    }

  *ans_1 = sc_1;
  *ans_2 = sc_2;
}


// for Problem 4
void
culc_Tk_4 (double *R, double *X, int n, double *ans_1, double *ans_2)
{

  int j;
  double sc_1 = 0, sc_2 = 0, tmp;

  /* R = r_k X = Ar_k and sc_1 = <X, R> sc_2 = <X, X> */
  for (j = 0; j < n; j++)
    {
      tmp = X[j];
      sc_1 += R[j] * tmp;
      sc_2 += tmp * tmp;
    }

  *ans_1 = sc_1;
  *ans_2 = sc_2;
}



// Problem 5
void
problem_5 (double *A, double *X0, double *X, double *B, double *R, int m, int n)
{
  int i, j;
  double t, sc_1, sc_2, tmp, *pA;

  Ax_b (A, X0, R, B, n); /* r_0 = Ax_0 - b -> R */

  for (i = 0; i < m; i++)
    {
      AD_1x (A, R, X, n);	/* A(D^-1)r_k -> X */

      sc_1 = 0;
      sc_2 = 0;
      pA = A;

      /* R = r_k X = A(D^-1)r_k and <(D^-1)R, R> и <X, (D^-1)R> */
      for (j = 0; j < n; j++)
        {
          if (!(*pA < 0 || *pA > 0))
            {
              printf ("\nERROR: A[%d, %d] = 0\n", j, j);
              return;
            }

          tmp = R[j];
          sc_1 += tmp * tmp / *pA;
          sc_2 += X[j] * tmp / *pA;
          pA += n + 1;
        }

      if (!(sc_2 < 0 || sc_2 > 0))
        {
          printf ("\nERROR: Scalar product = 0\n");
          return;
        }

      t = sc_1 / sc_2;

      if (!(t < 0 || t > 0))
        {
          printf ("\nERROR: Inv scalar product = 0\n");
          return;
        }

      pA = A;
      for (j = 0; j < n; j++) /* x_k - t_k [b - Ax_k] -> X0 */
        {
          X0[j] -= t * R[j] / *pA; /* x_k+1 = x_k - t_k(D^-1)[r_k] -> X0 */
          R[j] -= t * X[j];  /* r_k+1 = r_k - t_k [Ar_k] -> R */
          pA += n + 1;
        }
    }

  for (i = 0; i < n; i++)
    X[i] = X0[i];
}




// Problem 6
void
problem_6 (double *A, double *X0, double *X, double *B, double *R, int m, int n)
{
  int i, j;
  double t, sc_1, sc_2, *pA;

  Ax_b (A, X0, R, B, n); /* r_0 = Ax_0 - b -> R */

  for (i = 0; i < m; i++)
    {
      AD_1x (A, R, X, n);	/* A(D^-1)r_k -> X */

      sc_1 = 0;
      sc_2 = 0;

      /* R = r_k X = A(D^-1)r_k and sc_1 = <X, R> и sc_2 = <X, X> */
      culc_Tk_4 (R, X, n, &sc_1, &sc_2);

      if (!(sc_2 < 0 || sc_2 > 0))
        {
          printf ("\nERROR: Scalar product = 0\n");
          return;
        }

      t = sc_1 / sc_2;

      if (!(t < 0 || t > 0))
        {
          printf ("\nERROR: Inv scalar product = 0\n");
          return;
        }

      pA = A;
      for (j = 0; j < n; j++) /* x_k - t_k [b - Ax_k] -> X0 */
        {
          X0[j] -= t * R[j]/ *pA;; /* x_k+1 = x_k - t_k(D^-1)[r_k] -> X0 */
          R[j] -= t * X[j];  /* r_k+1 = r_k - t_k [Ar_k] -> R */
          pA += n + 1;
        }
    }

  for (i = 0; i < n; i++)
    X[i] = X0[i];
}



// Problem 7 - Jacobi
void
problem_7 (double *A, double *X0, double *X, double *B, double *R, double t, int m, int n)
{
  int i, j;
  double *pA;
  (void) R;

  for (i = 0; i < m; i++)
    {
      Ax_b (A, X0, X, B, n);  /* Ax_k - b -> X */

      pA = A;

      /* x_k+1 = x_k - t (D^-1) [Ax_k - b] -> X0 */
      for (j = 0; j < n; j++)
        {
          if (!(*pA < 0 || *pA > 0))
            {
              printf ("\nERROR: A[%d, %d] = 0\n", j, j);
              return;
            }

          X0[j] -= t * X[j] / *pA;
          pA += n + 1;
        }
    }

  for (i = 0; i < n; i++)
    X[i] = X0[i];
}



// Problem 8 - Gauss-Seidel
void
problem_8 (double *A, double *X0, double *X, double *B, double *R, double *W, double t, int m, int n)
{
  int i, j, ret;
  (void) W;

  for (i = 0; i < m; i++)
    {
      Ax_b (A, X0, R, B, n);  /* Ax_k - b -> R */

      ret = culc_Lx (A, X, R, n);  /* solve (D + L)x = .. - > X */
      if (ret)
        return;

      for (j = 0; j < n; j++)
        X0[j] -= t * X[j];
    }

  for (i = 0; i < n; i++)
    X[i] = X0[i];
}



// Problem 9 - Inverse Gauss-Seidel
void
problem_9 (double *A, double *X0, double *X, double *B, double *R, double *W, double t, int m, int n)
{
  int i, j, ret;
  (void) W;

  for (i = 0; i < m; i++)
    {
      Ax_b (A, X0, R, B, n);  /* Ax_k - b-> R */

      ret = culc_Rx (A, X, R, n);  /* solve (D + R)x = .. - > X */
      if (ret)
        return;

      for (j = 0; j < n; j++)
        X0[j] -= t * X[j];
    }

  for (i = 0; i < n; i++)
    X[i] = X0[i];
}



// Problem 10 - SSOR
void
problem_10 (double *A, double *X0, double *X, double *B, double *R, double *W, double t, int m, int n)
{
  int i, j, ret;
  double *pA;
  (void) W;

  for (i = 0; i < m; i++)
    {
      Ax_b (A, X0, R, B, n);  /* Ax_k - b -> R */

      ret = culc_Lx (A, X, R, n);  /* solve (D + L)x = ..  - > X */
      if (ret)
        return;

      pA = A;
      for (j = 0; j < n; j++)  /* D * X -> X */
        {
          X[j] *= *pA;
          pA += n + 1;
        }

      ret = culc_Rx (A, R, X, n);  /* solve (D + R)x = ..  - > R */
      if (ret)
        return;

      for (j = 0; j < n; j++)
        X0[j] -= t * R[j];
    }

  for (i = 0; i < n; i++)
    X[i] = X0[i];
}
