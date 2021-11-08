#include "residual.h"
#include "func_base.h"
#include "unit_tests_base.h"

void
calc_residual (
    const params_t &params, const vect &results,
    residual_t &all_residual_g, residual_t &all_residual_v)
{
  vect diff_g, diff_v;
  fill_diff_vect (params, results, diff_g, diff_v);
  calc_all_norm (params, diff_g, diff_v, all_residual_g, all_residual_v);
}

void
calc_residual (
    const params_t &params, const vect &res_1, const vect &res_2,
    residual_t &all_residual_g, residual_t &all_residual_v, const int k)
{
  vect diff_g, diff_v;
  fill_diff_vect (params, res_1, res_2, diff_g, diff_v, k);
  calc_all_norm (params, diff_g, diff_v, all_residual_g, all_residual_v);
}


void
fill_diff_vect (const params_t &params, const vect &results,
                vect &diff_g, vect &diff_v)
{
  double t = params.N * params.tau;

  for (size_t m = 0; m <= params.M; m++)
    {
      double x = m * params.h;

      double val_g = fabs (results[G(m)] - g (t, x));
      double val_v = fabs (results[V(m)] - u (t, x));

      diff_g.push_back (val_g);
      diff_v.push_back (val_v);
    }
}

void
fill_diff_vect (const params_t &params,
                const vect &res_1, const vect &res_2,
                vect &diff_g, vect &diff_v, const int k)
{
  Assert (res_1.size () == params.size,
          "fill_diff_vect: check size res_1");
  Assert (res_2.size () == 2 * (k * params.M + 1),
          "fill_diff_vect: check size res_2");

  for (size_t m = 0; m <= params.M; m++)
    {
      double val_g = fabs (res_1[G(m)] - res_2[G(m * k)]);
      double val_v = fabs (res_1[V(m)] - res_2[V(m * k)]);

      diff_g.push_back (val_g);
      diff_v.push_back (val_v);
    }
}

/* ============================================================================ */

void
calc_all_norm (
    const params_t &params, const vect &diff_g, const vect &diff_v,
    residual_t &all_residual_g, residual_t &all_residual_v)
{
  all_residual_g.C = C_norm (diff_g);
  all_residual_v.C = C_norm (diff_v);

  all_residual_g.L = L2_norm (diff_g, params.h);
  all_residual_v.L = L2_norm (diff_v, params.h);

  all_residual_g.W = W2_1h_norm (diff_g, params.h);
  all_residual_v.W = W2_1h_norm (diff_v, params.h);
}


double
C_norm (const vect &v)
{
  auto max_elem = *(std::max_element (v.begin(), v.end()));
  return (max_elem < 0.) ? NAN : max_elem;
}

double
L2_norm (const vect &v, double h)
{
  double scal = 0.;
  int size = static_cast<int> (v.size ());

  for (int i = 1; i < size - 1; i++)
    scal += v[i] * v[i];

  scal += 0.5 * v[0] * v[0];
  scal += 0.5 * v[size - 1] * v[size - 1];

  return sqrt (h * scal);
}

double
W2_1h_norm (const vect  &v, double h)
{
  double first = L2_norm (v, h);
  double second = 0.;

  int size = static_cast<int> (v.size ());

  for (int i = 0; i < size - 1; i++)
    second += (v[i + 1] - v[i]) * (v[i + 1] - v[i]);

  second /= h;
  return sqrt (first * first + second);
}



