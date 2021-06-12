#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets/QtWidgets>

#include "addition.h"
#include "approximation.h"

#define DEFAULT_A -10
#define DEFAULT_B 10
#define DEFAULT_N 10
#define DEFAULT_M 1000
#define DEFAULT_K 0
#define DEFAULT_INFO_H 150

constexpr double MIN_DIST = 1.e-6;
constexpr double MAX_DIST = 1.e30;

enum class Displayed_type
{
  shift_newton,
  cubic_spline,
  both_methods,
  both_error
};

class Window : public QWidget
{
  Q_OBJECT

private:
  double a = DEFAULT_A;
  double b = DEFAULT_B;
  int n = DEFAULT_N;

  int func_id = DEFAULT_K;
  const char *f_name;
  double (*f) (double);
  double (*ddf) (double);

  int m = DEFAULT_M; // width of graph area
  int h = DEFAULT_M; // height of graph area

  int p = 0; // delta coef
  int s = 0; // zoom coef

  bool fl_recalc = 1;
  double max_etalon = 0;
  double dr_max = 0;
  double dr_min = 0;

  Displayed_type displayed_graph = Displayed_type::shift_newton;

  std::unique_ptr <Approximation> approx_newton;
  std::unique_ptr <Approximation> approx_spline;

  std::vector<double> draw_x_etalon;
  std::vector<double> draw_fx_etalon;

public:
  friend class def_func;
  Window (QWidget *parent);

  QSize minimumSizeHint () const;
  QSize sizeHint () const;

  int parse_command_line (int argc, char *argv[]);
  void print_debag ();


  // === initialization === //
  void init_start_data (std::vector<double> &x, std::vector<double> &fx);
  void init_in_paint_data (std::vector<double> &in);
  void init_draw_point_etalon ();
  void init_start_approx_data (Approximation &approx);


  // === calculate out === //
  std::pair<double, double> get_min_max ();
  std::pair<double, double> get_displayed_min_max (double min_e, double max_e, double min_s, double max_s);

  void calc_approx_out (Approximation &approx, bool recalc);
  void calc_diff (Approximation &approx);


  // === paint action === //
  void make_coordinate_transform (QPainter &painter, double max_y, double min_y);
  void paint_graph (std::vector<double>  &x, std::vector<double>  &fx, QPainter &painter, QPen &pen);
  void paint_axis (QPainter &painter);
  void paint_info (QPainter &painter, double max_y, double min_y);
  void beauty_dash_pen (QPen &pen);

  int draw_x (double t);
  int draw_y (double t);


  // === SLOTS === //
  void set_recalc ();
  void set_func ();
  void set_big_n ();
  int zoom (double coef);

public slots:
  void change_func ();
  void change_graph ();

  void zoom_in ();
  void zoom_out ();

  void double_n ();
  void half_n ();

  void add_delta ();
  void subtract_delta ();

  void set_n_10 ();
  void set_n_input ();
  void set_a_input ();
  void set_b_input ();
  void set_k_input ();

protected:
  void paintEvent (QPaintEvent *event);
};

#endif // WINDOW_H
