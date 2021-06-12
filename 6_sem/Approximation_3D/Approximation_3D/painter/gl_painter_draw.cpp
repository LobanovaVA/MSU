#include "painter/gl_painter.h"

void correct_wh (double &w, double &h)
{
  auto correct_small = [] (double &v)
  {
      if (fabs (v) < EPS)
        v = EPS;
    };

  correct_small (w);
  correct_small (h);
}

void
Gl_painter::paintGL()
{
  Grid_info *grid;
  grid = surf->get_grid ();

  double max_w = grid->get_width ();
  double max_h = grid->get_height ();
  correct_wh  (max_w, max_h);

  // рисовать на всем окне
  int side = qMax (width (), height ());
  glViewport ((width () - side) / 2, (height () - side) / 2, side, side);

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity ();

  glRotated (xRot, 1.0, 0.0, 0.0);
  glRotated (yRot, 0.0, 1.0, 0.0);
  glRotated (270, 1.0, 0.0, 0.0);

  glDisable (GL_CULL_FACE);

  draw_axes ();
  //draw_axes_DEBAG();

  point_2d center; // here (0;0)
  grid->get_middle (center);
  //printf("center point = (%10.3e;%10.3e)\n", center.x, center.y);

  double zoom = std::pow (2, s);
  glTranslated (-zoom * center.x , -zoom * center.y, 0);
  glScaled (zoom / max_w, zoom / max_h, 1);
  glTranslated (center.x * max_w , center.y * max_h, 0);

  glEnableClientState (GL_VERTEX_ARRAY);
  glEnableClientState (GL_NORMAL_ARRAY);
  {
    glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable (GL_COLOR_MATERIAL);

    draw_surface ();
    draw_shadow ();
  }
  glDisableClientState (GL_VERTEX_ARRAY);
  glDisableClientState (GL_NORMAL_ARRAY);
}

void
Gl_painter::draw_axes ()
{
  int len  = qMax (width (), height());

  glEnable (GL_LINE_STIPPLE);
  {
    glLineWidth (2.0);
    glLineStipple (5, 0xAAAA);

    // positive part
    qglColor (QColor (190, 180, 120));
    glBegin (GL_LINE_LOOP);
    {
      glVertex3d (len, 0.0, 0.0);
      glVertex3d (0.0, 0.0, 0.0);

      glVertex3d (0.0, len, 0.0);
      glVertex3d (0.0, 0.0, 0.0);

      glVertex3d (0.0, 0.0, len);
      glVertex3d (0.0, 0.0, 0.0);
    }
    glEnd ();

    // negative part
    qglColor (QColor (70, 70, 50));
    glBegin (GL_LINE_LOOP);
    {
      glVertex3d ( 0.0,  0.0,  0.0);
      glVertex3d (-len,  0.0,  0.0);

      glVertex3d ( 0.0,  0.0,  0.0);
      glVertex3d ( 0.0, -len,  0.0);

      glVertex3d ( 0.0,  0.0,  0.0);
      glVertex3d ( 0.0,  0.0, -len);
    }
    glEnd ();
  }
  glDisable (GL_LINE_STIPPLE);
}

void
Gl_painter::draw_axes_DEBAG ()
{
  int len  = qMax (width (), height());
  glLineWidth (10.0);
  glBegin (GL_LINES);
  qglColor (Qt::red);
  glVertex3d ( len,  0.0,  0.0);
  glVertex3d (0/*-len*/,  0.0,  0.0);

  qglColor (Qt::green);
  glVertex3d ( 0.0,  len,  0.0);
  glVertex3d ( 0.0, 0/*-len*/,  0.0);

  qglColor (Qt::blue);
  glVertex3d ( 0.0,  0.0,  len);
  glVertex3d ( 0.0,  0.0, 0/*-len*/);
  glEnd ();
}


void
Gl_painter::draw_surface ()
{
  qglColor (QColor(255, 0, 200));
  surf->draw ();
}

void
Gl_painter::draw_shadow ()
{
  qglColor (Qt::lightGray);
  surf->draw_shadow ();
}

