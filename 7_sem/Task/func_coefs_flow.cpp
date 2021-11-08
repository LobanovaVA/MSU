#include "func_coef.h"
#include "structs.h"
#include "addition.h"

#include <math.h>

/* ============================================================================ */

coefficient_flow::coefficient_flow (
    const data_t &data_, const params_t &params_,
    const eigen_vector_t &GV_curr_)
  : data (data_), params(params_), GV(GV_curr_)
{
  fr_h = 1. / params.h;
  fr_tau = 1. / params.tau;
  tilde_mu = calc_tilde_mu ();
}

double
coefficient_flow::calc_tilde_mu () const
{
  double min = GV[G(0)];

  for (size_t m = 0; m <= params.M; m++)
    min = std::min (min, GV[G(m)]);

  return data.mu * std::exp (-min);
}


/* ============================================================================ */

double
coefficient_flow::G_G_m_minus (const size_t m) const
{
  double val = GV[V(m)] + GV[V(m-1)];
  return - val * frac_h (4);
}

double
coefficient_flow::G_G_m (const size_t /*m*/) const
{
  return fr_tau;
}

double
coefficient_flow::G_G_m_plus (const size_t m) const
{
  double val = GV[V(m)] + GV[V(m+1)];
  return val * frac_h (4);
}

double
coefficient_flow::G_V_m_minus (const size_t /*m*/) const
{
  return - frac_h (2);
}

double
coefficient_flow::G_V_m_plus  (const size_t /*m*/) const
{
  return frac_h (2);
}

/* ============================================================================ */

double
coefficient_flow::V_G_m_minus (const size_t m) const
{
  double val_tilde_p_rho = tilde_p_rho (std::exp (GV[G(m)]), data);
  return - val_tilde_p_rho * frac_h (2);
}

double
coefficient_flow::V_G_m_plus  (const size_t m) const
{
  double val_tilde_p_rho = tilde_p_rho (std::exp (GV[G(m)]), data);
  return val_tilde_p_rho * frac_h (2);
}

double
coefficient_flow::V_V_m_minus (const size_t m) const
{
  double val_V = GV[V(m)] + GV[V(m-1)];
  double val_mu = tilde_mu * frac_h (1) * frac_h (1);
  return - val_V * frac_h (6) - val_mu;
}

double
coefficient_flow::V_V_m (const size_t /*m*/) const
{
  return fr_tau + 2. * tilde_mu * frac_h (1) * frac_h (1);
}

double
coefficient_flow::V_V_m_plus  (const size_t m) const
{
  double val_V = GV[V(m)] + GV[V(m+1)];
  double val_mu = tilde_mu * frac_h (1) * frac_h (1);
  return val_V * frac_h (6) - val_mu;
}

/* ============================================================================ */

double
coefficient_flow::G_M_1 () const
{
  return - (GV[V(params.M - 1)] +GV[V(params.M)]) * frac_h (2);
}

double
coefficient_flow::G_M () const
{
  return fr_tau + GV[V(params.M)] * frac_h (1);
}

/* ============================================================================ */

double
coefficient_flow::rhs_G_m (const size_t m) const
{
  double val_V = (GV[V(m+1)] - GV[V(m-1)]) * frac_h (4);
  return GV[G(m)] * (fr_tau + val_V);
}

double
coefficient_flow::rhs_G_M () const
{
  const size_t M = params.M;

  double gv_210 = GV[G(M-2)] * GV[V(M-2)]
      - 2 * GV[G(M-1)] * GV[V(M-1)] + GV[G(M)] * GV[V(M)];
  double gv_321 = GV[G(M-3)] * GV[V(M-3)]
      - 2 * GV[G(M-2)] * GV[V(M-2)] + GV[G(M-1)] * GV[V(M-1)];

  double g_210 = GV[G(M-2)] - 2 * GV[G(M-1)] + GV[G(M)];
  double g_321 = GV[G(M-3)] - 2 * GV[G(M-2)] + GV[G(M-1)];

  double v_M = GV[V(M)];
  double g_M = GV[G(M)] * fr_tau;

  return  g_M
      - frac_h (2) * (gv_210 + v_M * g_210)
      + frac_h (4) * (gv_321 + v_M * g_321);
}


double
coefficient_flow::rhs_V_m (const size_t m) const
{
  double v_M = GV[V(m)] * fr_tau;
  double mu = tilde_mu - data.mu * std::exp (-GV[G(m)]);
  double v101 = GV[V(m-1)] - 2 * GV[V(m)] + GV[V(m+1)];
  return v_M - mu * v101 * frac_h (1) * frac_h (1);
}

double
coefficient_flow::rhs_V_M () const
{
  return 0;
}
