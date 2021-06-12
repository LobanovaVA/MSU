#ifndef SURFACE_H
#define SURFACE_H

#include <QObject>
#include <QWidget>
#include <QGLWidget>

#include "addition.h"
#include "grid_info.h"
#include "struct.h"

#define PAINT_SIZE 64

class Surface
{
private:
  func f;
  Grid_info *grid;
  std::unique_ptr<Grid_info> grid_ptr;
  Displayed_type displayed = Displayed_type::etalon;

  std::vector<double> f_coeffs;
  std::vector<double> etalon;
  std::vector<double> approx;

  minmax f_minmax = {1, -1};
  double max_z = 0.;
  double p = 0.;

public:
  Surface (Grid_info *grid_, func f_);

// === change params === //
  void set_func (func f_) { f = f_; };
  void change_displ ();
  void change_p (int n);

// === update data === //
  void update_coeffs ();
  void update_f_coeffs ();
  void update (Grid_info *grid_);
  void update (std::unique_ptr<Grid_info> &grid_ptr_);
  void set_approx (std::vector<double> &approx_) { approx.swap (approx_);};

// === get params === //
  double get_fmax () const;
  int get_p () const { return p; }
  Grid_info *get_grid () const { return grid/*.get ()*/; }

// === draw action === //
  void draw ();
  void draw_all_triangle ();
  void draw_shadow ();
  void draw_triangle (point_2d &P1, point_2d &P2, point_2d &P3);

private:
  void fill_etalon ();
  void fill_residual ();
  void find_minmax ();

};

#endif // SURFACE_H
