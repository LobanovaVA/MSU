#include <cmath>
#include <algorithm>
#include <iostream>

#include "approximation.h"
#include "msr_matr/msr_matr.h"

Approximation::Approximation (int th_p_, double eps_, int *I_, double *A_, double *rhs_,
                              double *x_, double *u_, double *r_, double *v_, double *buf_,
                              Grid_info *grid_, func f_, pthread_barrier_t *barrier_)
{
  th_p = th_p_;
  eps = eps_;

  I = I_;
  A = A_;

  rhs = rhs_;
  x = x_;

  u = u_;
  r = r_;
  v = v_;
  buf = buf_;

  f = f_;
  grid = grid_;

  grid -> get_nx_ny (nx, ny);

  barrier = barrier_;
}

void
Approximation::solve (int th_k)
{
  min_residual_solve_full (A, I, get_matrix_size (nx, ny), rhs, x, r, u, v,
                           buf, eps, MAX_IT, th_p, th_k, barrier);
}

void
Approximation::fill_carcass ()
{
  fill_I_diag (nx, ny, I);
}

void
Approximation::fill_matrix (int th_k)
{
  fill_A_full (nx, ny, A, I, th_p, th_k);
}

void
Approximation::fill_rhs (int th_k)
{
  int l1, l2;
  get_ind_thread (get_matrix_size (nx, ny), th_p, th_k, l1, l2);

  for (int l = l1; l < l2; l++)
    rhs[l] = fill_rhs_l (nx, ny, l);
}

double
Approximation::fill_rhs_l (int nx, int ny, int l)
{
  int i, j;
  l2ij (nx, ny, i, j, l);

  int nx2 = 2 * nx;
  int ny2 = 2 * ny;

  double ans = 0;

  /* узлы в внутри */
  if (0 < i && i < nx && 0 < j && j < ny)
    {
      double ans36
          = grid->get_f_value_ij (f, 2 * i    , 2 * j    , nx2, ny2);
      double ans20
          = grid->get_f_value_ij (f, 2 * i + 1, 2 * j    , nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i + 1, 2 * j + 1, nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i    , 2 * j + 1, nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i - 1, 2 * j    , nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i - 1, 2 * j - 1, nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i    , 2 * j - 1, nx2, ny2);
      double ans4
          = grid->get_f_value_ij (f, 2 * i + 2, 2 * j + 1, nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i + 1, 2 * j + 2, nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i - 1, 2 * j + 1, nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i - 2, 2 * j - 1, nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i - 1, 2 * j - 2, nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i + 1, 2 * j - 1, nx2, ny2);
      double ans2
          = grid->get_f_value_ij (f, 2 * i + 2, 2 * j    , nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i + 2, 2 * j + 2, nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i    , 2 * j + 2, nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i - 2, 2 * j    , nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i - 2, 2 * j - 2, nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i    , 2 * j - 2, nx2, ny2);

      ans = ans36 * 36 + ans20 * 20 + ans4 * 4 + ans2 * 2;
      //fprintf(stderr, "1 i = %d j = %d, ans = %10.3e\n", i, j, ans);
      return ans / 192.;
    }

  /* узлы на границе - левый */
  if (i == 0  && 0 < j && j < ny)
    {
      double ans18
          = grid->get_f_value_ij (f, 2 * i    , 2 * j    , nx2, ny2);
      double ans20
          = grid->get_f_value_ij (f, 2 * i + 1, 2 * j    , nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i + 1, 2 * j + 1, nx2, ny2);
      double ans10
          = grid->get_f_value_ij (f, 2 * i    , 2 * j + 1, nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i    , 2 * j - 1, nx2, ny2);
      double ans4
          = grid->get_f_value_ij (f, 2 * i + 2, 2 * j + 1, nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i + 1, 2 * j + 2, nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i + 1, 2 * j - 1, nx2, ny2);
      double ans2
          = grid->get_f_value_ij (f, 2 * i + 2, 2 * j    , nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i + 2, 2 * j + 2, nx2, ny2);
      double ans1
          = grid->get_f_value_ij (f, 2 * i    , 2 * j + 2, nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i    , 2 * j - 2, nx2, ny2);

      ans = ans18* 18 + ans20 * 20 + ans10 * 10 + ans4 * 4 + ans2 * 2 + ans1;
      //fprintf(stderr, "2 i = %d j = %d, ans = %10.3e\n", i, j, ans);
      return ans / 192.;
    }

  /* узлы на границе - правый */
  if (i == nx && 0 < j && j < ny)
    {
      double ans18
          = grid->get_f_value_ij (f, 2 * i    , 2 * j    , nx2, ny2);
      double ans20
          = grid->get_f_value_ij (f, 2 * i - 1, 2 * j    , nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i - 1, 2 * j - 1, nx2, ny2);
      double ans10
          = grid->get_f_value_ij (f, 2 * i    , 2 * j + 1, nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i    , 2 * j - 1, nx2, ny2);
      double ans4
          = grid->get_f_value_ij (f, 2 * i - 1, 2 * j + 1, nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i - 2, 2 * j - 1, nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i - 1, 2 * j - 2, nx2, ny2);
      double ans2
          = grid->get_f_value_ij (f, 2 * i - 2, 2 * j    , nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i - 2, 2 * j - 2, nx2, ny2);
      double ans1
          = grid->get_f_value_ij (f, 2 * i    , 2 * j + 2, nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i    , 2 * j - 2, nx2, ny2);

      ans = ans18* 18 + ans20 * 20 + ans10 * 10 + ans4 * 4 + ans2 * 2 + ans1;
      //fprintf(stderr, "3 i = %d j = %d, ans = %10.3e\n", i, j, ans);
      return ans / 192.;
    }

  /* узлы на границе - нижний */
  if (j == 0  && 0 < i && i < nx)
    {
      double ans18
          = grid->get_f_value_ij (f, 2 * i    , 2 * j    , nx2, ny2);
      double ans20
          = grid->get_f_value_ij (f, 2 * i + 1, 2 * j + 1, nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i    , 2 * j + 1, nx2, ny2);
      double ans10
          = grid->get_f_value_ij (f, 2 * i + 1, 2 * j    , nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i - 1, 2 * j    , nx2, ny2);
      double ans4
          = grid->get_f_value_ij (f, 2 * i + 2, 2 * j + 1, nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i + 1, 2 * j + 2, nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i - 1, 2 * j + 1, nx2, ny2);
      double ans2
          = grid->get_f_value_ij (f, 2 * i + 2, 2 * j + 2, nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i    , 2 * j + 2, nx2, ny2);
      double ans1
          = grid->get_f_value_ij (f, 2 * i + 2, 2 * j    , nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i - 2, 2 * j    , nx2, ny2);

      ans = ans18 * 18 + ans20 * 20 + ans10 * 10 + ans4 * 4 + ans2 * 2 + ans1;
      //fprintf(stderr, "4 i = %d j = %d, ans = %10.3e\n", i, j, ans);
      return ans / 192.;
    }

  /* узлы на границе - верхний */
  if (j == ny && 0 < i && i < nx)
    {
      double ans18
          = grid->get_f_value_ij (f, 2 * i    , 2 * j    , nx2, ny2);
      double ans20
          = grid->get_f_value_ij (f, 2 * i - 1, 2 * j - 1, nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i    , 2 * j - 1, nx2, ny2);
      double ans10
          = grid->get_f_value_ij (f, 2 * i + 1, 2 * j    , nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i - 1, 2 * j    , nx2, ny2);
      double ans4
          = grid->get_f_value_ij (f, 2 * i - 2, 2 * j - 1, nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i - 1, 2 * j - 2, nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i + 1, 2 * j - 1, nx2, ny2);
      double ans2
          = grid->get_f_value_ij (f, 2 * i - 2, 2 * j - 2, nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i    , 2 * j - 2, nx2, ny2);
      double ans1
          = grid->get_f_value_ij (f, 2 * i + 2, 2 * j    , nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i - 2, 2 * j    , nx2, ny2);

      ans = ans18 * 18 + ans20 * 20 + ans10 * 10 + ans4 * 4 + ans2 * 2 + ans1;
      //fprintf(stderr, "5 i = %d j = %d, ans = %10.3e\n", i, j, ans);
      return ans / 192.;
    }

  /* узел на углу - 0 0 */
  if (j == 0 && i == 0)
    {
      double ans12
          = grid->get_f_value_ij (f, 2 * i    , 2 * j    , nx2, ny2);
      double ans20
          = grid->get_f_value_ij (f, 2 * i + 1, 2 * j + 1, nx2, ny2);
      double ans10
          = grid->get_f_value_ij (f, 2 * i + 1, 2 * j    , nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i    , 2 * j + 1, nx2, ny2);
      double ans4
          = grid->get_f_value_ij (f, 2 * i + 2, 2 * j + 1, nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i + 1, 2 * j + 2, nx2, ny2);
      double ans2
          = grid->get_f_value_ij (f, 2 * i + 2, 2 * j + 2, nx2, ny2);
      double ans1
          = grid->get_f_value_ij (f, 2 * i + 2, 2 * j    , nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i    , 2 * j + 2, nx2, ny2);

      ans = ans12 * 12 + ans20 * 20 + ans10 * 10 + ans4 * 4 + ans2 * 2 + ans1;
      //fprintf(stderr, "6 i = %d j = %d, ans = %10.3e\n", i, j, ans);
      return ans / 192.;
    }

  /* узел на углу  - nx ny */
  if (i == nx && j == ny)
    {
      double ans12
          = grid->get_f_value_ij (f, 2 * i    , 2 * j    , nx2, ny2);
      double ans20
          = grid->get_f_value_ij (f, 2 * i - 1, 2 * j - 1, nx2, ny2);
      double ans10
          = grid->get_f_value_ij (f, 2 * i - 1, 2 * j    , nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i    , 2 * j - 1, nx2, ny2);
      double ans4
          = grid->get_f_value_ij (f, 2 * i - 2, 2 * j - 1, nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i - 1, 2 * j - 2, nx2, ny2);
      double ans2
          = grid->get_f_value_ij (f, 2 * i - 2, 2 * j - 2, nx2, ny2);
      double ans1
          = grid->get_f_value_ij (f, 2 * i - 2, 2 * j    , nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i    , 2 * j - 2, nx2, ny2);

      ans = ans12 * 12 + ans20 * 20 + ans10 * 10 + ans4 * 4 + ans2 * 2 + ans1;
      //fprintf(stderr, "7 i = %d j = %d, ans = %10.3e\n", i, j, ans);
      return ans / 192.;
    }

  /* узел на углу  - 0 ny */
  if (i == 0 && j == ny)
    {
      double ans6
          = grid->get_f_value_ij (f, 2 * i    , 2 * j    , nx2, ny2);
      double ans10
          = grid->get_f_value_ij (f, 2 * i + 1, 2 * j    , nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i    , 2 * j - 1, nx2, ny2);
      double ans4
          = grid->get_f_value_ij (f, 2 * i + 1, 2 * j - 1, nx2, ny2);
      double ans1
          = grid->get_f_value_ij (f, 2 * i + 2, 2 * j    , nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i    , 2 * j - 2, nx2, ny2);

      ans = ans6 * 6 + ans10 * 10 + ans4 * 4 + ans1;
      //fprintf(stderr, "8 i = %d j = %d, ans = %10.3e\n", i, j, ans);
      return ans / 192.;
    }

  /* узел на углу  - nx 0 */
  if (i == nx && j == 0)
    {
      double ans6
          = grid->get_f_value_ij (f, 2 * i    , 2 * j    , nx2, ny2);
      double ans10
          = grid->get_f_value_ij (f, 2 * i    , 2 * j + 1, nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i - 1, 2 * j    , nx2, ny2);
      double ans4
          = grid->get_f_value_ij (f, 2 * i - 1, 2 * j + 1, nx2, ny2);
      double ans1
          = grid->get_f_value_ij (f, 2 * i    , 2 * j + 2, nx2, ny2)
          + grid->get_f_value_ij (f, 2 * i - 2, 2 * j    , nx2, ny2);

      ans = ans6 * 6 + ans10 * 10 + ans4 * 4 + ans1;
      //fprintf(stderr, "9 i = %d j = %d, ans = %10.3e\n", i, j, ans);
      return ans / 192.;
    }

  fprintf (stderr, "FATAL ERROR: fill_rhs_l\n");
  abort ();
  return -1;
}
