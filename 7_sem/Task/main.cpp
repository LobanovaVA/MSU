#include <iostream>

#include "unit_tests.h"
#include "structs.h"
#include "in_out.h"
#include "scheme.h"
#include "residual.h"
#include "func_base.h"

enum task_type {
  DEBUG_TEST_SIMPLE = 1,
  DEBUG_TEST_NESTED_GRIDS,
  NONSMOOTH_TEST_1,
  NONSMOOTH_TEST_2,
  OSCILLATING_TEST_1,
  OSCILLATING_TEST_2,
  FLOW_TEST,
  FLOW_TEST_DUMP
};

void task_1 (const data_t &data, const params_t &params, const int K_max = 1);
void task_2 (const data_t &data, const params_t &params,
             const std::function <double(const double, const double)> F_g,
             const std::function <double(const double, const double)> F_u);
void task_3 (const data_t &data, const params_t &params,
             const std::function <double(const double, const double, const size_t)> F_g_k,
             const std::function <double(const double, const double, const size_t)> F_u_k);
void task_4 (const data_t &data, const params_t &params,
             const size_t step_num = 4, const bool dump = false);

/* ============================================================================ */

int main (int argc, char **argv)
{
  TestAll ();

  int mode = 0;
  data_t data;
  params_t params;

  if (get_args (argc, argv, mode, data, params) != err_type::NO_ERROR)
    return print_usage (argv[0]), 0;

  switch (mode)
    {
    case task_type::DEBUG_TEST_SIMPLE:
      task_1 (data, params);
      break;
    case task_type::DEBUG_TEST_NESTED_GRIDS:
      task_1 (data, params, 4);
      break;
    case task_type::NONSMOOTH_TEST_1:
      task_2 (data, params, g_1, u_1);
      break;
    case task_type::NONSMOOTH_TEST_2:
      task_2 (data, params, g_2, u_2);
      break;
    case task_type::OSCILLATING_TEST_1:
      task_3 (data, params, g_3, u_3);
      break;
    case task_type::OSCILLATING_TEST_2:
      task_3 (data, params, g_4, u_4);
      break;
    case task_type::FLOW_TEST:
      task_4 (data, params);
      break;
    case task_type::FLOW_TEST_DUMP:
      task_4 (data, params, 1, true);
      break;
    }

  return err_type::NO_ERROR;
}

/* ============================================================================ */

void task_1 (const data_t &data, const params_t &params, const int K_max)
{
  std::vector<vect> all_result (K_max);
  stop_result_t stop_result/*unused*/;
  residual_t residual_g, residual_v;

  params_t params_edit;
  params_edit.fill (params.N, params.M, data);

  scheme_solver solver (data, params, all_result[0], stop_result, g, u);
  solver.run ();

  for (int k = 1; k < K_max; k++)
    {
      params_edit.fill (2 * params_edit.N, 2 * params_edit.M, data);

      scheme_solver solver (data, params_edit, all_result[k], stop_result, g, u);
      solver.run ();

      calc_residual (params, all_result[0], all_result[k],
                     residual_g, residual_v, 1 << k);

      residual_g.print ();
    }

  calc_residual (params, all_result[0], residual_g, residual_v);
  residual_g.print ();
}

void task_2 (const data_t &data, const params_t &params,
             const std::function <double(const double, const double)> F_g,
             const std::function <double(const double, const double)> F_u)
{
  vect result/*unused*/;
  stop_result_t stop_result;

  scheme_solver solver (data, params, result, stop_result, F_g, F_u);

  solver.run_until_found_N0_dump ();
  solver.run_table_stop ();

  stop_result.set_time_step (params.tau);
  stop_result.print_residual_V ();
  stop_result.print_diff_mass ();
}

void task_3 (const data_t &data, const params_t &params,
             const std::function <double(const double, const double, const size_t)> F_g_k,
             const std::function <double(const double, const double, const size_t)> F_u_k)
{
  vect result/*unused*/;
  stop_result_t stop_result;

  for (size_t k = 1; k <= params.M / 10; k++)
    {
      auto F_g = [&] (const double t, const double x) { return F_g_k (t, x, k); };
      auto F_u = [&] (const double t, const double x) { return F_u_k (t, x, k); };

      scheme_solver solver (data, params, result, stop_result, F_g, F_u);
      solver.run_until_found_N0 ();

      stop_result.set_time_step (params.tau);
      stop_result.print_time_step ();
    }
}

void task_4 (const data_t &data, const params_t &params, const size_t step_num, const bool dump)
{
  vect result/*unused*/;
  stop_result_t stop_result;

  for (size_t tilde_rho = 1; tilde_rho <= step_num; tilde_rho++)
    for (size_t tilde_u = 1; tilde_u <= step_num; tilde_u++)
      {
        scheme_solver solver (data, params, result, stop_result, g_0, u_0);
        solver.run_until_found_N0_flow (log (tilde_rho), tilde_u, dump);

        stop_result.set_time_step (params.tau);
        stop_result.print_time_step ();
      }
}

