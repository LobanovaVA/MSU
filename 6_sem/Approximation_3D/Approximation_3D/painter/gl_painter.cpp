#include "gl_painter.h"

Gl_painter::Gl_painter (Grid_info *grid, func f, QWidget *parent) : QGLWidget (parent)
{
  surf.reset (new Surface (grid, f));
}

void
Gl_painter::set_Window (Window *window)
{
  this->window = window;
}

void
Gl_painter::initializeGL()
{
  qglClearColor (QColor(48, 10, 36));  // цвет фона графика
  glEnable (GL_DEPTH_TEST); // глубина
  glEnable (GL_CULL_FACE);  // отбрасывать невидимое
  glShadeModel (GL_SMOOTH); // сглаживание

  light_setting ();
}

void
Gl_painter::light_setting () const
{
  glEnable (GL_LIGHTING);
  glEnable (GL_LIGHT0);
  glEnable (GL_LIGHT2);

  GLfloat mat_specular [] = {1.0, 1.0, 1.0, 1.0};
  GLfloat mat_shininess [] = {50,0};
  GLfloat light_position_0 [] = {20.0, 20.0, 10.0, 10.0 }; //{20.0, 20.0, 5.0, 10.0};
  GLfloat light_position_2 [] = {0.0, 0.0, 1., 1};

  glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv (GL_FRONT, GL_SHININESS, mat_shininess);
  glLightfv (GL_LIGHT0, GL_POSITION, light_position_0);
  glLightfv (GL_LIGHT2, GL_DIFFUSE, light_position_2);
}

void
Gl_painter::resizeGL(int width, int height)
{
  int side = qMin (width, height);
  glViewport ((width - side) / 2, (height - side) / 2, side, side);

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();

#ifdef QT_OPENGL_ES_1
  glOrtho(-2, 2, -1, 1, -1, 1);
#else
  glOrtho(-2, 2, -2, 2, -2, 2);
#endif

  glMatrixMode(GL_MODELVIEW);
}

QSize
Gl_painter::minimumSizeHint () const
{
  return QSize (500, 500);
}

QSize
Gl_painter::sizeHint () const
{
  return QSize (1000, 1000);
}
