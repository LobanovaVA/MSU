#include "in_out.h"
#include "structs.h"
#include "addition.h"
#include "residual.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <fstream>

#define PRINT(x) std::cout << #x << " = " << x << "; ";
#define PRINT_E(x) printf ("%10.6e ", x);
#define PRINT_FL(x) printf ("%.4f ", x);

void
print_usage (const std::string& hint)
{
  std::cerr << "Usage: " << hint << " MODE T X C gamma mu N M" << std::endl;
}

int
get_args (const int argc, char **argv, int& mode, data_t &data, params_t &params)
{
  if (argc != 9)
    return err_type::USAGE_ARGC;

  if (!(sscanf (argv[1], "%d", &mode) == 1 && mode > 0 && mode < 9))
    return err_type::USAGE_ARGC;

  size_t N_, M_;
  if (! (sscanf (argv[2], "%lf", &data.T) == 1 && data.T > 0
      && sscanf (argv[3], "%lf", &data.X) == 1 && data.X > 0
      && sscanf (argv[4], "%lf", &data.C) == 1 && data.C > 0
      && sscanf (argv[5], "%lf", &data.gamma) == 1 && data.gamma > 0
      && sscanf (argv[6], "%lf", &data.mu) == 1 && data.mu > 0

      && sscanf (argv[7], "%lu", &N_) == 1 && N_ > 0
      && sscanf (argv[8], "%lu", &M_) == 1 && M_ > 0 ))
    return err_type::USAGE_ARGC;

  params.fill (N_, M_, data);

  std::stringstream ss;
  ss << mode << "_" << data.C << "_" << data.gamma << "_" << data.mu << "_"
     << params.N << "_" << params.M << ".txt";
  data.name = ss.str ();

#ifdef DEBUG
  data.print();
  params.print();
#endif

  return err_type::NO_ERROR;
}

/* ============================================================================ */

void data_t::print ()
{
  PRINT (T)
  PRINT (X)
  PRINT (C)
  PRINT (gamma)
  PRINT (mu)
  std::cout << std::endl;
}

void params_t::print ()
{
  PRINT (M)
  PRINT (N)
  PRINT (size)
  PRINT (h)
  PRINT (tau)
  std::cout << std::endl;
}

void residual_t::print ()
{
  PRINT_E (C);
  PRINT_E (L);
  PRINT_E (W);
}

void stop_result_t::print_residual_V ()
{
  print_time_step ();
  PRINT_E (stop_residual_V[1]);
  PRINT_E (stop_residual_V[3]);
  PRINT_E (stop_residual_V[5]);
  PRINT_E (stop_residual_V[7]);
  std::cout << std::endl;
}

void stop_result_t::print_diff_mass ()
{
  PRINT_E (stop_diff_mass[0]);
  PRINT_E (stop_diff_mass[2]);
  PRINT_E (stop_diff_mass[4]);
  PRINT_E (stop_diff_mass[6]);
  PRINT_E (stop_diff_mass[7]);
  std::cout << std::endl;
}

void stop_result_t::print_time_step ()
{
  PRINT_FL (time_step);
}


void
stop_result_t::open_files (const std::string &name,
                           const double tau, const double h)
{
  file_norm_V.open ("norm_V" + name);
  file_diff_mass.open ("diff_mass_" + name);
  file_all_G.open ("all_G_" + name);
  file_all_V.open ("all_V_" + name);

  file_all_G << tau << " " << h << std::endl;
  file_all_V << tau << " " << h << std::endl;
}

void
stop_result_t::dump_in_files (const eigen_vector_t &GV,
                              const double V_norm, const double diff_mass)
{
  file_norm_V << V_norm << std::endl;
  file_diff_mass << diff_mass << std::endl;

  dump_in_files (GV);
}

void
stop_result_t::dump_in_files (const eigen_vector_t &GV)
{
  for (long int i = 0; i < GV.size () / 2; i += 5)
    {
      file_all_G << GV[G(i)] << " ";
      file_all_V << GV[V(i)] << " ";
    }
  file_all_G << std::endl;
  file_all_V << std::endl;
}


void
stop_result_t::close_files ()
{
  file_norm_V.close ();
  file_diff_mass.close ();
  file_all_G.close ();
  file_all_V.close ();
}

/* ============================================================================ */

#if 0

void write_table (const std::vector<residual_t> &res)
{
//  std::cout << std::scientific << "C = " << res.C << "  |  "
//            << std::scientific << "L = " << res.L << "  |  "
//            << std::scientific << "W = " << res.W << std::endl;
}

void
create_table (const params_t &params, vect &result, const std::string& filename)
{
  auto [residual_g, residual_v] = calc_residual (params, result);

  write_table ("G", residual_g, filename);
  write_table ("V", residual_v, filename);

  write_table_tex ("G", residual_g, filename);
  write_table_tex ("V", residual_v, filename);
}

void write_table (const std::string& var_name,
                  const residual_t &res, const std::string& filename)
{
  std::ofstream outfile;
  outfile.open(filename, std::ios_base::app);

  outfile << var_name << ": "
          << std::scientific << "C = " << res.C << "  |  "
          << std::scientific << "L = " << res.L << "  |  "
          << std::scientific << "W = " << res.W << std::endl;
}

void write_table_tex (const std::string& var_name,
                      const residual_t &res, const std::string& filename)
{
  return;
}

#endif
