#include "scheme.h"
#include "addition.h"
#include "func_base.h"

#include <string>
#include <iostream>
#include <fstream>

#define PRINT_E(x) printf ("%10.6e ", x);

scheme_solver::scheme_solver (const data_t &data_, const params_t &params_,
                              vect &result_, stop_result_t &stop_result_,
                              const std::function <double(const double, const double)> F_g_,
                              const std::function <double(const double, const double)> F_u_)
  : data (data_), params (params_), result (result_),
    stop_result (stop_result_), F_g (F_g_), F_u (F_u_)
{
  const size_t size = params.size;
  GV_curr.resize (size);
  matrix.resize (size, size);
  rhs.resize (size);
}

void
scheme_solver::init_start_vector ()
{
  for (size_t m = 0; m <= params.M; m++)
    {
      double x = params.h * m;
      GV_curr[G(m)] = F_g (0., x);
      GV_curr[V(m)] = F_u (0., x);
    }
}

void
scheme_solver::save_result () const
{
  result.clear ();
  for (size_t i = 0; i < params.size; i++)
    result.push_back (GV_curr[i]);
}

void
scheme_solver::print_for_err (const int code_err) const
{
  fprintf (stderr, "ERROR #%d: C = %3.0f  mu = %5.4f  N = %4lu M = %4lu\n",
           code_err, data.C, data.mu, params.N, params.M);
}

/* ============================================================================ */

int
scheme_solver::run ()
{
  init_start_vector ();

  for (size_t n = 0; n < params.N; n++)
    {
      coefficient coef (data, params, GV_curr, n, f0, f);
      scheme_builder builder (params.M, coef, matrix, rhs);
      builder.fill_system ();

      eigen_solver_t solver (matrix);

      if (solver.info () != Eigen::Success)
        {
          fprintf (stderr, "ERROR: Can not build preconditioner\n");
          print_for_err (solver.info ());
          return err_type::PRECOND;
        }

      eigen_vector_t GV_next = solver.solveWithGuess (rhs, GV_curr);

      GV_curr = GV_next;
    }

  save_result ();
  return err_type::NO_ERROR;
}

/* ============================================================================ */

int
scheme_solver::run_until_found_N0_dump ()
{
  const double eps = 1e-2;

  stop_result.open_files (data.name, params.tau, params.h);

  init_start_vector ();

  stop_result.start_sum_mass = sum_exp_G ();

  for (size_t n = 0; ; n++)
    {
      {
        coefficient coef (data, params, GV_curr, n, f0_const, f_const);
        scheme_builder builder (params.M, coef, matrix, rhs);
        builder.fill_system ();

        eigen_solver_t solver (matrix);

        if (solver.info () != Eigen::Success)
          {
            fprintf (stderr, "ERROR: Can not build preconditioner\n");
            print_for_err (solver.info ());
            return err_type::PRECOND;
          }

        eigen_vector_t GV_next = solver.solveWithGuess (rhs, GV_curr);

        GV_curr = GV_next;
      }

      {
        double V_norm = C_norm_only_V ();
        double diff_mass = sum_exp_G () / stop_result.start_sum_mass - 1.;

        std::vector<unsigned int> cut = {0, 1, 2, 3, 5, 10, 20, 30, 60, 120, 180};
        for (auto item : cut)
          if (n * params.tau == item)
            stop_result.dump_in_files (GV_curr, V_norm, diff_mass);

        if (V_norm < eps)
          {
            stop_result.N0 = n;
            stop_result.dump_in_files (GV_curr, V_norm, diff_mass);
            break;
          }
      }
    }

  stop_result.close_files ();

  return err_type::NO_ERROR;
}

int
scheme_solver::run_table_stop ()
{
  const size_t N0 = stop_result.N0;
  init_start_vector ();

  size_t n = 0;
  vect all_stop_steps = {0.2, 0.25, 0.4, 0.5, 0.6, 0.75, 0.8, 1};

  for (const double coef : all_stop_steps)
    {
      size_t stop_step = coef * N0;

      for (; n < stop_step; n++)
        {
          coefficient coef (data, params, GV_curr, n, f0_const, f_const);
          scheme_builder builder (params.M, coef, matrix, rhs);
          builder.fill_system ();

          eigen_solver_t solver (matrix);

          if (solver.info () != Eigen::Success)
            {
              fprintf (stderr, "ERROR: Can not build preconditioner\n");
              print_for_err (solver.info ());
              return err_type::PRECOND;
            }

          eigen_vector_t GV_next = solver.solveWithGuess (rhs, GV_curr);

          GV_curr = GV_next;
        }

      stop_result.stop_residual_V.push_back (C_norm_only_V ());
      double end_sum_mass = sum_exp_G ();
      stop_result.stop_diff_mass.push_back (
            end_sum_mass / stop_result.start_sum_mass - 1.);
    }

  return err_type::NO_ERROR;
}

/* ============================================================================ */

int
scheme_solver::run_until_found_N0 ()
{
  const double eps = 1e-3;
  init_start_vector ();

  for (size_t n = 0; ; n++)
    {
      {
        coefficient coef (data, params, GV_curr, n, f0_const, f_const);
        scheme_builder builder (params.M, coef, matrix, rhs);
        builder.fill_system ();

        eigen_solver_t solver (matrix);

        if (solver.info () != Eigen::Success)
          {
            fprintf (stderr, "ERROR: Can not build preconditioner\n");
            print_for_err (solver.info ());
            return err_type::PRECOND;
          }

        eigen_vector_t GV_next = solver.solveWithGuess (rhs, GV_curr);

        GV_curr = GV_next;
      }

      if (C_norm_only_V () < eps)
        {
          stop_result.N0 = n;
          break;
        }
    }

  return err_type::NO_ERROR;
}

/* ============================================================================ */

int
scheme_solver::run_until_found_N0_flow (
    const double tilde_g, const double tilde_u, const bool dump)
{
  const double eps = 1e-2;
  const size_t check_step = 50;
  std::vector<vect> prev_results (check_step);

  if (dump)
    stop_result.open_files (data.name, params.tau, params.h);

  init_start_vector ();

  for (size_t n = 0; ; n++)
    {
      {
        coefficient_flow coef (data, params, GV_curr);
        scheme_builder_flow builder (params.M, coef, matrix, rhs);
        builder.fill_system (tilde_g, tilde_u);

        eigen_solver_t solver (matrix);

        if (solver.info () != Eigen::Success)
          {
            fprintf (stderr, "ERROR: Can not build preconditioner\n");
            print_for_err (solver.info ());
            return err_type::PRECOND;
          }

        eigen_vector_t GV_next = solver.solveWithGuess (rhs, GV_curr);

        GV_curr = GV_next;
      }

      if (dump)
        {
          vect cut = {0, 0.1, 0.2, 0.3, 0.5, 1, 2, 3, 6, 7};
          for (auto item : cut)
            if (n * params.tau == item)
              stop_result.dump_in_files (GV_curr);
        }

      {
        save_result ();
        if (n > check_step && C_norm_V_flow (prev_results[0]) < eps)
          {
            stop_result.N0 = n;
            stop_result.dump_in_files (GV_curr);
            break;
          }

        if (n < check_step)
          std::copy (result.begin (), result.end (), std::back_inserter (prev_results[n]));
        else
          {
            for (size_t j = 1; j < check_step; j++)
              prev_results[j - 1] = std::move (prev_results[j]);
            std::copy (result.begin (), result.end (), std::back_inserter (prev_results[check_step - 1]));
          }
      }
    }

  if (dump)
    stop_result.close_files ();

  return err_type::NO_ERROR;
}

/* ============================================================================ */

double
scheme_solver::C_norm_only_V () const
{
  double max = fabs (GV_curr[V(0)]);
  double fabs_V;

  for (size_t i = 0; i < params.size / 2; i++)
    {
      fabs_V = fabs (GV_curr[V(i)]);
      max = (fabs_V > max) ? fabs_V : max;
    }

  return (max < 0.) ? NAN : max;
}

double
scheme_solver::C_norm_V_flow (const vect &prev) const
{
  double max = fabs (result[V(0)] - prev[V(0)]);
  double fabs_V;

  for (size_t i = 0; i < params.size / 2; i++)
    {
      fabs_V = fabs (result[V(i)] - prev[V(i)]);
      max = (fabs_V > max) ? fabs_V : max;
    }

  return (max < 0.) ? NAN : max;
}


double
scheme_solver::sum_exp_G () const
{
  double sum = 0;

  for (size_t m = 0; m < params.size / 2; m++)
    sum += std::exp (GV_curr[G(m)]);

  return sum;
}














