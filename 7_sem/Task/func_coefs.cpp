#include "func_coef.h"
#include "structs.h"
#include "addition.h"

#include <math.h>

double
tilde_p_rho (const double g, const data_t &data)
{
  /* \dfrac{\partial p}{\partial \rho}(x) */
  return data.C * data.gamma * std::pow (g, data.gamma - 1);
}

/* ============================================================================ */

coefficient::coefficient (const data_t &data_, const params_t &params_,
                          const eigen_vector_t &GV_curr_, const size_t n,
                          const std::function <double(const double, const double)> f0_,
                          const std::function <double(const double, const double, const data_t &data)> f_)
  : data (data_), params(params_), GV(GV_curr_), time_step (n), F_f0 (f0_), F_f (f_)
{
  fr_h = 1. / params.h;
  fr_tau = 1. / params.tau;
  tilde_mu = calc_tilde_mu ();
}

double
coefficient::calc_tilde_mu () const
{
  double min = GV[G(0)];

  for (size_t m = 0; m <= params.M; m++)
    min = std::min (min, GV[G(m)]);

  return data.mu * std::exp (-min);
}

/* ============================================================================ */

double
coefficient::coefficient::G_0 () const
{
  return fr_tau; // V_{0}^n=0:  - GV[V(0)] * frac_h (2);
}

double coefficient::G_1 () const
{
  return GV[V(1)] * frac_h (2);
}

double
coefficient::V_0 () const
{
  return - frac_h (1);
}

double coefficient::V_1 () const
{
  return frac_h (1);
}

/* ============================================================================ */

double
coefficient::G_G_m_minus (const size_t m) const
{
  double val = GV[V(m)] + GV[V(m-1)];
  return - val * frac_h (4);
}

double
coefficient::G_G_m (const size_t /*m*/) const
{
  return fr_tau;
}

double
coefficient::G_G_m_plus (const size_t m) const
{
  double val = GV[V(m)] + GV[V(m+1)];
  return val * frac_h (4);
}

double
coefficient::G_V_m_minus (const size_t /*m*/) const
{
  return - frac_h (2);
}

double
coefficient::G_V_m_plus  (const size_t /*m*/) const
{
  return frac_h (2);
}

/* ============================================================================ */

double
coefficient::V_G_m_minus (const size_t m) const
{
  double val_tilde_p_rho = tilde_p_rho (std::exp (GV[G(m)]), data);
  return - val_tilde_p_rho * frac_h (2);
}

double
coefficient::V_G_m_plus  (const size_t m) const
{
  double val_tilde_p_rho = tilde_p_rho (std::exp (GV[G(m)]), data);
  return val_tilde_p_rho * frac_h (2);
}

double
coefficient::V_V_m_minus (const size_t m) const
{
  double val_V = GV[V(m)] + GV[V(m-1)];
  double val_mu = tilde_mu * frac_h (1) * frac_h (1);
  return - val_V * frac_h (6) - val_mu;
}

double
coefficient::V_V_m (const size_t /*m*/) const
{
  return fr_tau + 2. * tilde_mu * frac_h (1) * frac_h (1);
}

double
coefficient::V_V_m_plus  (const size_t m) const
{
  double val_V = GV[V(m)] + GV[V(m+1)];
  double val_mu = tilde_mu * frac_h (1) * frac_h (1);
  return val_V * frac_h (6) - val_mu;
}

/* ============================================================================ */

double
coefficient::G_M_1 () const
{
  return - GV[V(params.M - 1)] * frac_h (2);
}

double
coefficient::G_M () const
{
  return fr_tau + GV[V(params.M)] * frac_h (2);
}

double
coefficient::V_M_1 () const
{
  return - frac_h (1);
}

double
coefficient::V_M () const
{
  return frac_h (1);
}

/* ============================================================================ */

double
coefficient::rhs_G_0 () const
{
  double g_0 = GV[G(0)]
      * (fr_tau + frac_h (2) * (GV[V(1)] - GV[V(0)]));

  double gv_012 = GV[G(0)] * GV[V(0)]
      - 2 * GV[G(1)] * GV[V(1)] + GV[G(2)] * GV[V(2)];

  double gv_123 = GV[G(1)] * GV[V(1)]
      - 2 * GV[G(2)] * GV[V(2)] + GV[G(3)] * GV[V(3)];

  double v_012 = GV[V(0)] - 2 * GV[V(1)] + GV[V(2)];
  double v_123 = GV[V(1)] - 2 * GV[V(2)] + GV[V(3)];

  double add = 2. - GV[G(0)];

  return F_f0 ((1 + time_step) * params.tau, 0 * params.h) + g_0
      + frac_h (2) * (gv_012 + add * v_012)
      - frac_h (4) * (gv_123 + add * v_123);
}

double
coefficient::rhs_G_m (const size_t m) const
{
  double val_V = (GV[V(m+1)] - GV[V(m-1)]) * frac_h (4);
  return F_f0 ((1 + time_step) * params.tau, m * params.h)
      + GV[G(m)] * (fr_tau + val_V);
}

double
coefficient::rhs_G_M () const
{
  const size_t M = params.M;

  double gv_210 = GV[G(M-2)] * GV[V(M-2)]
      - 2 * GV[G(M-1)] * GV[V(M-1)] + GV[G(M)] * GV[V(M)];
  double gv_321 = GV[G(M-3)] * GV[V(M-3)]
      - 2 * GV[G(M-2)] * GV[V(M-2)] + GV[G(M-1)] * GV[V(M-1)];

  double v_210 = GV[V(M-2)] - 2 * GV[V(M-1)] + GV[V(M)];
  double v_321 = GV[V(M-3)] - 2 * GV[V(M-2)] + GV[V(M-1)];

  double add = 2. - GV[G(M)];
  double g_M = GV[G(M)]
      * (fr_tau + (GV[V(M)] - GV[V(M-1)]) * frac_h (2));

  return F_f0 ((1 + time_step) * params.tau, M * params.h) + g_M
      - frac_h (2) * (gv_210 + add * v_210)
      + frac_h (4) * (gv_321 + add * v_321);
}

double
coefficient::rhs_V_0 () const
{
  return 0;
}

double
coefficient::rhs_V_m (const size_t m) const
{
  double v_M = GV[V(m)] * fr_tau;
  double mu = tilde_mu - data.mu * std::exp (-GV[G(m)]);
  double v101 = GV[V(m-1)] - 2 * GV[V(m)] + GV[V(m+1)];
  return v_M - mu * v101 * frac_h (1) * frac_h (1)
      + F_f ((1 + time_step) * params.tau, m * params.h, data);
}

double
coefficient::rhs_V_M () const
{
  return 0;
}
