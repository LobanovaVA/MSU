#include "gl_painter.h"

void
Gl_painter::set_func (func f)
{
  surf->set_func (f);
}

void
Gl_painter::change_displ ()
{
  surf->change_displ ();
}

void
Gl_painter::zoom_in ()
{
  s++;
  updateGL ();
}

void
Gl_painter::zoom_out ()
{
  s--;
  updateGL ();
}

void
Gl_painter::add_delta ()
{
  surf->change_p (0);
  update_surface_coeffs ();
  updateGL();
}
void
Gl_painter::subtract_delta ()
{
  surf->change_p (1);
  update_surface_coeffs ();
  updateGL ();
}

void
Gl_painter::rot_clock ()
{
  yRot -= 15;
  yRot %= 360;
  rh++;
  rh = (rh % 24) ? rh : 0;
  update ();
}

void
Gl_painter::rot_unclock ()
{
  yRot += 15;
  yRot %= 360;
  rh--;
  rh = (rh % 24) ? rh : 0;
  update ();
}

void
Gl_painter::rot_up ()
{
  xRot -= 15;
  yRot %= 360;
  rv++;
  rv = (rv % 24) ? rv : 0;
  update ();
}

void
Gl_painter::rot_down ()
{
  xRot += 15;
  xRot %= 360;
  rv--;
  rv = (rv % 24) ? rv : 0;
  update ();
}


void
Gl_painter::update_surface_coeffs ()
{
  surf->update_coeffs ();
}

void
Gl_painter::update_surface (std::unique_ptr<Grid_info> &grid)
{
  surf->update (grid/*.get()*/);
}

void
Gl_painter::set_approx (std::vector<double> &approx)
{
  surf->set_approx (approx);
}

double
Gl_painter::get_fmax ()
{
  return surf->get_fmax ();
}

