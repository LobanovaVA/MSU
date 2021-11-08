#ifndef FUNC_COEF_H
#define FUNC_COEF_H

#include "structs.h"

class coefficient
{
private:
  const data_t &data;
  const params_t &params;

  const eigen_vector_t &GV;
  const size_t time_step;

  const std::function <double(const double, const double)> F_f0;
  const std::function <double(const double, const double, const data_t &data)> F_f;

  double fr_h = 0;
  double fr_tau = 0;
  double tilde_mu = 0;

private:
  inline double frac_h (double k) const { return fr_h / k; }
  double calc_tilde_mu () const;

public:
  coefficient (const data_t &data_, const params_t &params_,
               const eigen_vector_t &GV_curr_, const size_t n,
               const std::function <double(const double, const double)> f0_,
               const std::function <double(const double, const double, const data_t &data)> f_);

  ~coefficient () = default;

  // m = 0  G: A*G_{0} + C*G_{1} + B*V_{0} + D*V_{1} = K_{0}^g //
  double G_0 () const;
  double G_1 () const;
  double V_0 () const;
  double V_1 () const;

  // m = 1...M-1  G: A*G_{m-1} + C*G_{m} + D*G_{m+1} + B*V_{m-1} + E*V_{m+1} = K_{m}^g //
  double G_G_m_minus (const size_t m) const;
  double G_G_m       (const size_t m) const;
  double G_G_m_plus  (const size_t m) const;

  double G_V_m_minus (const size_t m) const;
  double G_V_m_plus  (const size_t m) const;

  // m = 1...M-1  V: A*G_{m-1} + D*G_{m+1} + B*V_{m-1} + C*V_{m} + E*V_{m+1} = K_{m}^v //
  double V_G_m_minus (const size_t m) const;
  double V_G_m_plus  (const size_t m) const;

  double V_V_m_minus (const size_t m) const;
  double V_V_m       (const size_t m) const;
  double V_V_m_plus  (const size_t m) const;

  // m = M G: A*G_{M-1} + C*G_{M} + B*V_{M-1} + D*V_{M} = K_{M}^g //
  double G_M_1 () const;
  double G_M   () const;
  double V_M_1 () const;
  double V_M   () const;

  // rhs
  double rhs_G_0 () const;
  double rhs_G_m (const size_t m) const;
  double rhs_G_M () const;

  double rhs_V_0 () const;
  double rhs_V_m (const size_t m) const;
  double rhs_V_M () const;
};

/* ============================================================================ */

class coefficient_flow
{
private:
  const data_t &data;
  const params_t &params;

  const eigen_vector_t &GV;

  double fr_h = 0;
  double fr_tau = 0;
  double tilde_mu = 0;

private:
  inline double frac_h (double k) const { return fr_h / k; }
  double calc_tilde_mu () const;

public:
  coefficient_flow (const data_t &data_, const params_t &params_,
                    const eigen_vector_t &GV_curr_);

  ~coefficient_flow () = default;


  // m = 1...M-1  G: A*G_{m-1} + C*G_{m} + D*G_{m+1} + B*V_{m-1} + E*V_{m+1} = K_{m}^g //
  double G_G_m_minus (const size_t m) const;
  double G_G_m       (const size_t m) const;
  double G_G_m_plus  (const size_t m) const;

  double G_V_m_minus (const size_t m) const;
  double G_V_m_plus  (const size_t m) const;

  // m = 1...M-1  V: A*G_{m-1} + D*G_{m+1} + B*V_{m-1} + C*V_{m} + E*V_{m+1} = K_{m}^v //
  double V_G_m_minus (const size_t m) const;
  double V_G_m_plus  (const size_t m) const;

  double V_V_m_minus (const size_t m) const;
  double V_V_m       (const size_t m) const;
  double V_V_m_plus  (const size_t m) const;

  // m = M G: A*G_{M-1} + B*G_{M} = K_{M}^g //
  double G_M_1 () const;
  double G_M   () const;

  // rhs
  double rhs_G_m (const size_t m) const;
  double rhs_G_M () const;

  double rhs_V_m (const size_t m) const;
  double rhs_V_M () const;
};

#endif // FUNC_COEF_H
