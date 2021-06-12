#include <QPainter>
#include <stdio.h>

#include "window.h"

Window::Window (QWidget *parent) : QWidget (parent)
{
  approx_spline = std::make_unique <Approximation> (Method_type::cubic_spline);
  approx_newton = std::make_unique <Approximation> (Method_type::shift_newton);

  draw_x_etalon.reserve (1000000);
  draw_fx_etalon.reserve (1000000);

  for (int i = 0; i < 7; i++)
    change_func ();
}

QSize Window::minimumSizeHint () const
{
  return QSize (500, 500);
}

QSize Window::sizeHint () const
{
  return QSize (1000, 1000);
}

int Window::parse_command_line (int argc, char *argv[])
{
  switch (argc)
    {
    case 1:
      {
        print_message (Message_type::information, "Autoupdate arguments",
                       "No arguments.\nReset default values:\n  a = %4.d\n  b = %4.d\n  n = %4.d\n  k = %4.1d",
                       DEFAULT_A, DEFAULT_B, DEFAULT_N, DEFAULT_K);
        return 0;
      }
    case 2:
      return -1;
    case 3:
      {
        if (sscanf (argv[1], "%lf", &a) != 1  || sscanf (argv[2], "%lf", &b) != 1  || b - a < MIN_DIST)
          return -2;

        print_message (Message_type::information, "Autoupdate arguments",
                       "No arguments for n, k.\nReset default values:\n  n = %4.d\n  k = %4.1d",
                       DEFAULT_N, DEFAULT_K);
        return 0;
      }

    case 4:
      {
        if (sscanf (argv[1], "%lf", &a) != 1  || sscanf (argv[2], "%lf", &b) != 1  || b - a < MIN_DIST
            || sscanf (argv[3], "%d", &n) != 1 || n <= 0)
          return -2;

        print_message (Message_type::information, "Autoupdate arguments",
                       "No arguments for k.\nReset default values:\n  k = %4.1d", DEFAULT_K);
        return 0;
      }

    case 5:
      {
        if (sscanf (argv[1], "%lf", &a) != 1  || sscanf (argv[2], "%lf", &b) != 1  || b - a < MIN_DIST
            || sscanf (argv[3], "%d", &n) != 1 || n <= 0
            || sscanf (argv[4], "%d", &func_id) != 1 || func_id < 0 || func_id > 6)
          return -2;

        for (int i = 0; i < 7; i++)
          change_func ();

        return 0;
      }

    default:
      return  -2;
    }

  return 0;
}


void
Window::print_debag ()
{
  char msg[LEN];
  sprintf (msg, "k = %d n = %8.d p = %3.1d s = %3.1d a = %10.3e b = %10.3e mode = %d",
           func_id, n, p, s, a, b, (int) displayed_graph);
  qDebug() << msg;
}
