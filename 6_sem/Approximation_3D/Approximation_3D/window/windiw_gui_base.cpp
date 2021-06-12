#include "window/window.h"

extern bool calculating;

QSize
Window::minimumSizeHint () const
{
  return QSize (500, 500);
}

QSize
Window::sizeHint () const
{
  return QSize (1000, 1000);
}

void
Window::init_window_gui ()
{
  grid.reset (new Grid_info (nx, ny, pol));

  drawer = new  Gl_painter (grid.get (), f, this);
  drawer->set_Window (this);

  change_label ();
  init_label_layouts ();
}

void
Window::closeEvent (QCloseEvent *event)
{
  if (calculating)
    event->ignore ();
  else
    {
      for (int k = 0; k < threads_num; k++)
        th_info[k].proceed = false;

      th_out++;
      pthread_cond_broadcast (&cond);

      event->accept ();
    }
}
