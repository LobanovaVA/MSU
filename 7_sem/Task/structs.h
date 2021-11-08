#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>
#include <fstream>

#include <vector>
using vect = std::vector<double>;

#include <eigen/Eigen/Sparse>
using eigen_vector_t = Eigen::VectorXd;

struct data_t
{
  double T;
  double X;
  double C;
  double gamma;
  double mu;
  std::string name;

  void print ();
};

struct params_t
{
  size_t N;
  size_t M;
  size_t size;
  double tau;
  double h;

  void
  fill (double N_, double M_, const data_t &data)
  {
    N = N_;
    M = M_;
    size = 2 * (M_ + 1);
    tau = data.T / N_;
    h = data.X / M_;
  }
  void print ();
};

struct residual_t
{
  double C = 0;
  double L = 0;
  double W = 0;

  void print ();
};

struct stop_result_t
{
  size_t N0;
  double time_step;

  std::vector<double> stop_residual_V;

  std::vector<double> stop_diff_mass;
  double start_sum_mass;

  std::ofstream file_norm_V;
  std::ofstream file_diff_mass;
  std::ofstream file_all_G;
  std::ofstream file_all_V;

  void set_time_step (double tau)
  {
    time_step = tau * N0;
  }

  void print_residual_V ();
  void print_diff_mass ();
  void print_time_step ();

  void open_files (const std::string &name, const double tau, const double h);
  void dump_in_files (const eigen_vector_t &GV,
                      const double V_norm, const double diff_mass);
  void dump_in_files (const eigen_vector_t &GV);
  void close_files ();
};

double tilde_p_rho (const double g, const data_t &data);

#endif // STRUCTS_H
