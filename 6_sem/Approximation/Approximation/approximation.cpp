#include <cmath>
#include <algorithm>
#include <iostream>

#include "approximation.h"

Approximation::Approximation (Method_type _method) : method (_method)
{
  x.reserve (1000000);
  fx.reserve (1000000);
  in.reserve (5000);
  out.reserve (5000);

  rf.reserve (1000000);

  if (method == Method_type::cubic_spline)
    {
      d.reserve (1000000);
      a_d.reserve (1000000);
      a_up.reserve (1000000);
      a_low.reserve (1000000);
    }
}

void
Approximation::update (double _a, double _b, int _n, double _ddf1, double _ddfn)
{
  a = _a;
  b = _b;
  n = _n;
  ddf1 = _ddf1;
  ddfn = _ddfn;
}

void
Approximation::init_shift_newton_data ()
{
  int curr_shift, prev_shift = 0, i_loc;
  rf.resize (SHIFT * n - (SHIFT * (SHIFT - 1)) / 2);

  // calc f(x_i, x_i+1)
  for (int i = 0; i < n; i++)
    {
      rf[i] = fx[i + 1] - fx[i];
      if (std::abs (rf[i]) < EPS)
        rf [i] = 0;

      rf [i] /= (x[i + 1] - x[i]);
    }

  // calc others rf
  for (int count = 1; count < SHIFT; count++)
    {
      curr_shift = count * n - (count * (count - 1)) / 2;

      //for (int i = n - count - 1; i >= 0; i--)
      for (int i = 0; i < n - count; i++)
        {
         i_loc = curr_shift + i;
          rf[i_loc] = rf[prev_shift + i + 1] - rf[prev_shift + i];
          if (std::abs (rf[i_loc]) < EPS)
            rf [i_loc] = 0;

          rf [i_loc] /= (x[i + count + 1] - x[i]);
        }

      prev_shift = curr_shift;
    }
}

void
Approximation::init_cubic_spline_data ()
{
  rf.resize (n + 1);
  d.resize (n + 1);
  a_d.resize (n + 1);
  a_up.resize (n + 1);
  a_low.resize (n + 1);

  // == calc f(x_i, x_i+1) == //
  for (int i = 0; i < n; i++)
    {
      rf[i] = fx[i + 1] - fx[i];
      if (std::abs (rf[i]) < EPS)
        rf [i] = 0;

      rf [i] /= (x[i + 1] - x[i]);
    }

  // == calc matrix == //
  d[0] = 3 * rf[0] - 0.5 * ddf1 * (x[1] - x[0]);
  d[n] = 3 * rf[n - 1] + 0.5 * ddfn * (x[n] - x[n-1]);

  a_d[0] = a_d[n] = 2;
  a_up[0] = a_low[n] = 1;
  a_low[0] = a_up[n] = 0;

  for (int i = 1; i < n; i++)
    {
      a_d[i] = 2 * (x[i + 1] - x[i - 1]);
      a_up[i] = x[i] - x[i - 1];
      a_low[i] = x[i + 1] - x[i];

      d[i] = 3 * rf[i - 1] * a_low[i] + 3 * rf[i] * a_up[i];
    }

  solve_matrix (); // find coef d[i]

  // == calc coef of P == //
  // for spline coef: c1 = fx, c2 = d, c3 = a_d, c4 = a_up
  a_d[0] = (3 * rf[0] - 2 * d[0] - d[1]) / (x[1] - x[0]);
  a_up[0] = (d[0] + d[1] - 2 * rf[0]) / ((x[1] - x[0]) * (x[1] - x[0]));

  for (int i = 1; i < n; i++)
    {
      a_d[i] = (3 * rf[i] - 2 * d[i] - d[i + 1]) / a_low[i];
      a_up[i] = (d[i] + d[i + 1] - 2 * rf[i]) / (a_low[i] * a_low[i]);
    }
}


double
Approximation::approximate (double t)
{
  switch (method)
    {
    case Method_type::shift_newton:
      return approx_shift_newton (t);
    case Method_type::cubic_spline:
      return approx_cubic_spline (t);
    }

  return 0;
}

double
Approximation::approx_shift_newton (double t)
{
  int i = (int) (n * (t - a) / (b - a));
  if (i > n - SHIFT)
    i = n - SHIFT;

  int curr_shift;
  double ft = 0;
  for (int count = SHIFT - 1; count >= 0; count--)
    {
      curr_shift = count * n - (count * (count - 1)) / 2;
      ft += rf[curr_shift + i];
      ft *= (t - x[i + count]);
    }

  ft += fx[i];
  return ft;
}

double
Approximation::approx_cubic_spline (double t)
{
#ifdef TODO
  поиск i через итераторы вектора
#endif
  // for spline coef: c1 = fx, c2 = d, c3 = a_d, c4 = a_up
  int i = (int) (n * (t - a) / (b - a));
  t-=x[i];
  return fx[i] + d[i] * t + a_d[i] * t * t + a_up[i] * t * t * t;
}

void
Approximation::cacl_out (bool rewrite)
{
  if (rewrite)
    {
      if (method == Method_type::shift_newton)
        init_shift_newton_data ();

      if (method == Method_type::cubic_spline)
        init_cubic_spline_data ();
    }

  for (int i = 0; i < (int) in.size (); i++)
   out[i] = approximate (in[i]);
}


void is_small (double &t)
{
  if (std::abs (t) < EPS)
    t = 0;
}

void
Approximation::solve_matrix ()
{
  for (int i = 0; i < n; i++)
    {
      d[i] /= a_d[i];
      a_up[i] /= a_d[i];

      is_small(d[i]);
      is_small(a_up[i]);

      d[i + 1] -= d[i] * a_low[i + 1];
      a_d[i + 1] -= a_up[i] * a_low[i + 1];

      is_small(d[i + 1]);
      is_small(a_d[i + 1]);
    }

    d[n] /= a_d[n];

  for (int i = n; i > 0; i--)
    {
      d[i - 1] -= d[i] * a_up[i - 1];
      is_small(d[i - 1]);
    }
}

std::pair<double, double>
Approximation::get_min_max ()
{
  auto [min_y_iter, max_y_iter] = std::minmax_element (begin (out), end (out));
  return std::pair{*min_y_iter, *max_y_iter};
}

