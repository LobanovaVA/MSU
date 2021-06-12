#ifndef APPROX_METHOD_H
#define APPROX_METHOD_H

#include "addition.h"
#include "grid_info.h"

class Approximation
{
private:
    int nx = 1;
    int ny = 1;
    int th_p = 1;
    double eps = EPS;

    int *I = nullptr;
    double *A = nullptr;
    double *rhs = nullptr;
    double *x = nullptr;

    double *u = nullptr;
    double *r = nullptr;
    double *v = nullptr;
    double *buf = nullptr;

    Grid_info *grid;
    func f;

    pthread_barrier_t *barrier;

public:
  Approximation () = default;
  Approximation (int th_p_, double eps_, int *I_, double *A_, double *rhs_,
                 double *x_, double *u_, double *r_, double *v_, double *buf_,
                 Grid_info *grid_, func f_, pthread_barrier_t *barrier_);

  void solve (int th_k);
  void fill_carcass ();
  void fill_matrix (int th_k);
  void fill_rhs (int th_k);
  double fill_rhs_l (int nx, int ny, int l);
};

#endif // APPROX_METHOD_H
