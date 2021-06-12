#include <stdio.h>

#include "msr_matr.h"

void
min_residual_solve_full (double *A, int *I, int matrix_size, double *b, double *x, double *r, double *u, double *v,
                         double *buf, double eps, int maxit, int p, int k, pthread_barrier_t *barrier)
{
  int step = 50, it, ret = 0;
  for (it = 0; it < maxit; it+=step)
    {
      ret = min_residual_solve (A, I, matrix_size, b, x, r, u, v, buf, eps, step, p, k, barrier);
      if (ret > 0)
        break;
    }

  if (it >= maxit)
    fprintf (stderr, "ERROR: min_residual_solve_full maxit\n");

  if (k == 0)
    fprintf (stderr, "Finished at iter: %d, restarts = %d\n", it + ret, it / step);
}

int
min_residual_solve (double *A, int *I, int matrix_size, double *b, double *x, double *r, double *u, double *v,
                    double *buf, double eps, int maxit, int p, int k, pthread_barrier_t *barrier)
{
  int i1, i2, it;
  get_ind_thread (matrix_size, p, k, i1, i2);

  double b_norm = scalar_prod (matrix_size, b, b, buf, p, k, barrier);
  double eps_lim = eps * eps * b_norm;

  matr_mult_vector (matrix_size, A, I, x, r, p, k, barrier); /* r = Ax */
  lin_comb_vector (matrix_size, r, b, 1, p, k, barrier);     /* r -= b */

  for (it = 0; it < maxit; it++)
    {
      apply_precond_Jacobi (matrix_size, A, I, r, v, p, k, barrier); /* Mv = r */
      matr_mult_vector     (matrix_size, A, I, v, u, p, k, barrier); /* u = Av */

      double c1 = scalar_prod (matrix_size, u, r, buf, p, k, barrier);
      double c2 = scalar_prod (matrix_size, u, u, buf, p, k, barrier);

      if (c1 < eps_lim || c2 < eps_lim)
        break;

      double tau = c1 / c2;
      lin_comb_vector (matrix_size, x, v, tau, p, k, barrier); /* x -= v * tau */
      lin_comb_vector (matrix_size, r, u, tau, p, k, barrier); /* r -= u * tau */
    }

  if (it >= maxit)
    return -1;

  return it;
}
