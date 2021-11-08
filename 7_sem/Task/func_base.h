#ifndef FUNC_BASE_H
#define FUNC_BASE_H

#include "structs.h"

#include <eigen/Eigen/Sparse>
using eigen_vector_t  = Eigen::VectorXd;

/* ============================================================================ */

double rho (const double t, const double x);
double rho_t (const double t, const double x);
double rho_x (const double t, const double x);

double g (const double t, const double x);
double g_t (const double t, const double x);
double g_x (const double t, const double x);

double u (const double t, const double x);
double u_t (const double t, const double x);
double u_x (const double t, const double x);
double u_xx (const double t, const double x);

double f0 (const double t, const double x);
double f (const double t, const double x, const data_t &data);

/* ============================================================================ */

double f0_const (const double t, const double x);
double f_const (const double t, const double x, const data_t &data);

double rho_1 (const double t, const double x);
double g_1 (const double t, const double x);
double u_1 (const double t, const double x);

double rho_2 (const double t, const double x);
double g_2 (const double t, const double x);
double u_2 (const double t, const double x);

/* ============================================================================ */

double rho_3 (const double t, const double x, const size_t k);
double g_3 (const double t, const double x, const size_t k);
double u_3 (const double t, const double x, const size_t k);

double rho_4 (const double t, const double x, const size_t k);
double g_4 (const double t, const double x, const size_t k);
double u_4 (const double t, const double x, const size_t k);

/* ============================================================================ */

double rho_0 (const double t, const double x);
double g_0 (const double t, const double x);
double u_0 (const double t, const double x);

#endif // FUNC_BASE_H
