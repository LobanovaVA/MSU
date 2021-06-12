#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets/QtWidgets>
#include <QWidget>
#include <QHBoxLayout>

#include "addition.h"
#include "struct.h"
#include "grid_info.h"
#include "threads/thread_info.h"
#include "painter/gl_painter.h"



constexpr double MIN_DIST = 1.e-6;
constexpr double MAX_DIST = 1.e30;
class Gl_painter;

class Window : public QWidget
{
  Q_OBJECT

// === MEMBERS === //
private:
  int nx = 1;
  int ny = 1;
  int threads_num = 1;
  double eps = EPS;
  polygon *pol;

  int func_id;
  func f;
  func f_value[f_num_max];
  std::string f_names[f_num_max];

  std::unique_ptr<Grid_info> grid;
  std::unique_ptr<Grid_info> working_grid;

  Gl_painter *drawer;
  Displayed_type displayed = Displayed_type::etalon;
  bool fl_gui_changed = false; //state_changed_flag

  solver_data data;
  std::vector<double> answer;

  double window_time = 0.;

  std::unique_ptr<thread_info []> th_info;
  pthread_barrier_t barrier;
  pthread_cond_t cond;
  int th_out;


public:
  friend class def_func;
  Window (int nx_, int ny_, int f_k, int th_p,
          double eps_, polygon *pol_, QWidget *parent);

  ~Window ();
  QSize minimumSizeHint () const override;
  QSize sizeHint () const override;
  void closeEvent (QCloseEvent *event) override;

  void print_debug () const;
  void signal_calculation_completed ();
  void set_answer (double *result);


// === START ACTIONS === //
private:
  void init_window (int nx_, int ny_, int f_k, int th_p,
                    double eps_, polygon *pol_);
  void fill_f_arrays ();
  void init_window_gui ();
  void init_thread ();
  void start_threads ();

  void allocate_memory ();
  void init_th_info ();

  void before_calculation ();

// === LABELS === //
private:
  QLabel *nx_ny_label;
  QLabel *displ_label;
  QLabel *func_label;
  QLabel *fmax_label;
  QLabel *s_label;
  QLabel *p_label;
  QLabel *rh_label;
  QLabel *rv_label;

  void init_label_layouts ();
  void change_label ();
  void change_nx_ny_label ();
  void change_displ_label ();
  void change_func_label ();
  void change_fmax_label ();
  void change_s_label ();
  void change_p_label ();
  void change_rh_label ();
  void change_rv_label ();

// === NEED FOR SLOTS === //
private:
  void change_func_id ();
  void etalon_case ();
  void after_slot ();

// === SLOTS === //
public slots:
  void change_func ();
  void change_graph ();
  void zoom_in ();
  void zoom_out ();
  void double_n ();
  void half_n ();
  void add_delta ();
  void subtract_delta ();
  void rot_clock ();
  void rot_unclock ();
  void rot_up ();
  void rot_down ();

  void after_calculation ();

signals:
  void calculation_completed ();
};

#endif // WINDOW_H
