#ifndef GL_PAINTER_H
#define GL_PAINTER_H

#include "window/window.h"
#include "surface.h"

#define COEFF 1.2
#define COEFF2 2

class Window;
class Gl_painter: public QGLWidget
{
private:
  Window *window;
  std::unique_ptr<Surface> surf;

  int xRot = 30;
  int yRot = 225;
  int zRot = 0;

  int s = 0;
  int rh = 0;
  int rv = 0;


public:
  Gl_painter (Grid_info *grid, func f, QWidget *parent = nullptr);
  ~Gl_painter () {};

  void set_Window (Window *window);

private:
  void draw_axes();
  void draw_axes_DEBAG();
  void draw_surface ();
  void draw_shadow ();

// === from window SLOTS === //
public:
  void set_func (func f);
  void change_displ ();
  void zoom_in ();
  void zoom_out ();
  void add_delta ();
  void subtract_delta ();
  void rot_clock  ();
  void rot_unclock  ();
  void rot_up  ();
  void rot_down  ();

  void update_surface_coeffs ();
  void update_surface (std::unique_ptr<Grid_info> &grid);
  void set_approx (std::vector<double> &f_coeffs);

// === for window LABLES === //
public:
  double get_fmax ();
  int get_p () { return surf->get_p (); }
  int get_s () { return s; }
  int get_rh () { return rh; }
  int get_rv () { return rv; }

protected:
  QSize sizeHint () const;
  QSize minimumSizeHint () const;
  void initializeGL ();
  void paintGL ();
  void resizeGL (int width, int height);
  void light_setting () const;
};


#endif // GL_PAINTER_H
