#include "window.h"
#include <algorithm>

void /* initialization etalon points for approximation */
Window::init_start_data (std::vector<double> &x, std::vector<double> &fx)
{
  int size = x.size () - 1;

  double step = (b - a) / size;
  double arg = a;

  for (int i = 0; i < size + 1; i++, arg += step)
    {
      x[i] = arg;
      fx[i] = f (arg);
    }
}


void
Window::init_draw_point_etalon ()
{
  draw_x_etalon.resize (m + 1);
  draw_fx_etalon.resize (m + 1);

  int size = draw_x_etalon.size () - 1;
  double step = (b - a) / size;
  double arg = a;

  for (int i = 0; i < size + 1; i++, arg += step)
    {
      draw_x_etalon[i] = arg;
      draw_fx_etalon[i] = f (arg);
    }

  max_etalon = (*std::max_element (draw_fx_etalon.cbegin (), draw_fx_etalon.cend (),
                                   [] (double x, double y) { return std::abs (x) < std::abs (y); }));
}

void
Window::init_start_approx_data (Approximation &approx)
{
  auto &x = approx.x;
  auto &fx = approx.fx;
  auto &in = approx.in;
  auto &out = approx.out;

  x.resize (n + 1);
  fx.resize (n + 1);
  in.resize (m + 1);
  out.resize (m + 1);

  init_in_paint_data (in);

  if (fl_recalc)
    init_start_data (x, fx);

  fx[n / 2] += 0.1 * p * std::abs(max_etalon);
}


void /* initialization for paint points */
Window::init_in_paint_data (std::vector<double> &in)
{
  double B = b;
  double A = a;

  int size = in.size () - 1;
  double step = (B - A) / size;
  double arg = A;

  for (int i = 0; i < size + 1; i++, arg += step)
    in[i] = arg;
}

std::pair<double, double>
Window::get_min_max ()
{
  auto [min_y_iter, max_y_iter] = std::minmax_element (begin (draw_fx_etalon), end (draw_fx_etalon));
  return std::pair{*min_y_iter, *max_y_iter};
}

std::pair<double, double>
Window::get_displayed_min_max (double min_e, double max_e, double min_s, double max_s)
{
  double ans_min = 0, ans_max = 0;

  switch (displayed_graph)
    {
    case Displayed_type::shift_newton:
      ans_min = min_e;
      ans_max = max_e;
      break;
    case Displayed_type::cubic_spline:
      ans_min = std::min (min_e, min_s);
      ans_max = std::max (max_e, max_s);
      break;
    case Displayed_type::both_methods:
      ans_min = std::min (min_e, min_s);
      ans_max = std::max (max_e, max_s);
      break;
    case Displayed_type::both_error:
      ans_min = min_s;
      ans_max = max_s;
      break;
    }

  return std::pair{ans_min, ans_max};
}

void
Window::calc_approx_out (Approximation &approx, bool recalc)
{
  approx.update (a, b, n, ddf (approx.x[0]), ddf (approx.x[n]));
  approx.cacl_out (recalc);
}

void
Window::calc_diff (Approximation &approx)
{
  auto &in = approx.in;
  auto &out = approx.out;
  int len = in.size ();

  for (int i = 0; i < len; i++)
    out[i] = std::abs (draw_fx_etalon[i] - out[i]);
}
