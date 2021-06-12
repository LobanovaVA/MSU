#ifndef APPROX_METHOD_H
#define APPROX_METHOD_H

#include <vector>

#include "addition.h"

#define SHIFT 3

class Approximation
{
public:
  Method_type method;

  std::vector<double> x;
  std::vector<double> fx;
  std::vector<double> in;
  std::vector<double> out;

  double a;
  double b;
  int n;

  std::vector<double> rf;

  double ddf1 = 0;
  double ddfn = 0;

  std::vector<double> d;
  std::vector<double> a_d;
  std::vector<double> a_up;
  std::vector<double> a_low;
  // for spline coef: c1 = fx, c2 = d, c3 = a_d, c4 = a_up

public:
  Approximation (Method_type method = Method_type::shift_newton);

  void update (double _a, double _b, int _n, double _ddf1, double _ddfn);

  void init_shift_newton_data ();
  void init_cubic_spline_data ();

  double approximate (double t);
  double approx_shift_newton (double t);
  double approx_cubic_spline (double t);

  void cacl_out (bool rewrite);

  std::pair<double, double> get_min_max ();
  void solve_matrix ();

};

#endif // APPROX_METHOD_H
