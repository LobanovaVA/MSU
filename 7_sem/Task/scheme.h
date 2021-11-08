#ifndef SCHEME_H
#define SCHEME_H

#include "structs.h"
#include "func_coef.h"

using eigen_matrix_t  = Eigen::SparseMatrix<double>;
using eigen_triplet_t = Eigen::Triplet<double>;

using eigen_precond_t = Eigen::IncompleteLUT<double>;
using eigen_solver_t  = Eigen::BiCGSTAB<eigen_matrix_t, eigen_precond_t>;

/* ============================================================================ */

class scheme_builder
{
private:
  const size_t M;
  const coefficient &coef;

  eigen_matrix_t &matrix;
  eigen_vector_t &rhs;

  std::vector<eigen_triplet_t> triplets;

public:
  scheme_builder (const size_t M_, const coefficient &coef_,
                  eigen_matrix_t &matrix_, eigen_vector_t &rhs_);
  ~scheme_builder () = default;

  void fill_system ();

private:
  void equation_G_0 ();
  void equation_V_0 ();

  void equation_G_m (const size_t m);
  void equation_V_m (const size_t m);

  void equation_G_M ();
  void equation_V_M ();
};

class scheme_builder_flow
{
private:
  const size_t M;
  const coefficient_flow &coef;

  eigen_matrix_t &matrix;
  eigen_vector_t &rhs;

  std::vector<eigen_triplet_t> triplets;

public:
  scheme_builder_flow (const size_t M_, const coefficient_flow &coef_,
                       eigen_matrix_t &matrix_, eigen_vector_t &rhs_);
  ~scheme_builder_flow () = default;

  void fill_system (const double g_t0, const double u_t0);

private:
  void equation_G_0 (const double g_t0);
  void equation_V_0 (const double u_t0);

  void equation_G_m (const size_t m);
  void equation_V_m (const size_t m);

  void equation_G_M ();
  void equation_V_M ();
};

/* ============================================================================ */

class scheme_solver
{
private:
  const data_t &data;
  const params_t &params;

  vect &result;
  stop_result_t &stop_result;

  const std::function <double(const double, const double)> F_g;
  const std::function <double(const double, const double)> F_u;

  eigen_vector_t GV_curr;
  eigen_matrix_t matrix;
  eigen_vector_t rhs;

public:
  scheme_solver (const data_t &data_, const params_t &params_,
                 vect &result_, stop_result_t &stop_result_,
                 const std::function <double(const double, const double)> F_g_,
                 const std::function <double(const double, const double)> F_u_);
  ~scheme_solver () = default;

  int run ();
  int run_until_found_N0_dump ();
  int run_table_stop ();
  int run_until_found_N0 ();
  int run_until_found_N0_flow (
      const double tilde_g, const double tilde_u, const bool dump);

private:
  void init_start_vector ();
  void save_result () const;

  void print_for_err (const int code_err) const;
  double C_norm_only_V () const;
  double C_norm_V_flow (const vect &prev) const;
  double sum_exp_G () const;
};

#endif // SCHEME_H

/*
  === m = 0 ===
  G: A*G_{0} + B*V_{0} + C*G_{1} + D*V_{1} = K_{0}^g
  V: V_0 = 0

  |A B C D||.| |K_{0}^g|
  |0 1 0 0||.|=|   0   |
  |  ...  ||.| |   .   |

  === m = 1...M-1===
  G: A*G_{m-1} + B*V_{m-1} + C*G_{m} + D*G_{m+1} + E*V_{m+1} = K_{m}^g
  V: A*G_{m-1} + B*V_{m-1} + C*V_{m} + D*G_{m+1} + E*V_{m+1} = K_{m}^v //

  |    ...    ||.| |   .   |
  |A B C 0 D E||.| |K_{m}^g|
  |A B 0 C D E||.|=|K_{m}^v|
  |    ...    ||.| |   .   |

  === m = M ===
  G: A*G_{M-1} + B*V_{M-1} + C*G_{M} + D*V_{M} = K_{M}^g
  V: V_M = 0

  |  ...  ||.| |   .   |
  |A B C D||.| |K_{M}^g|
  |0 0 0 1||.|=|   0   |
*/
