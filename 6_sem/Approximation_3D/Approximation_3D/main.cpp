#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QAction>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMessageBox>

#include "window/window.h"
#include "struct.h"
#include "in_out.h"
#include "addition.h"

std::atomic <bool> calculating (true);

void make_toolbar (QMenuBar *tool_bar, Window *graph_area, QMainWindow *window);
void set_window (QMenuBar *tool_bar, Window *graph_area, QMainWindow *window);

int main (int argc, char *argv[])
{
  QApplication app (argc, argv);
  qApp->setFont (QFont ("Arial", 5));

  if (argc != 7)
    {
      print_message (Message_type::warning, "Wrong input arguments!", "ERROR: Usage: %s filename nx ny f_id EPS th_num\n", argv[0]);
      return ERR_USAGE_ARGC;
    }

  input_info in_info;
  polygon pol;

  int ret = parse_command_line (argv, in_info, pol);
  if (ret != NO_ERR)
    return ret;

  QMainWindow *window = new QMainWindow;
  QMenuBar *tool_bar = new QMenuBar (window);
  Window *graph_area = new Window (in_info.nx, in_info.ny, in_info.f_k,
                                   in_info.th_p, in_info.eps, &pol, window);

  make_toolbar (tool_bar, graph_area, window);
  set_window (tool_bar, graph_area, window);

  window->show ();
  app.exec ();

  delete graph_area;
  delete tool_bar;
  delete window;

  return NO_ERR;
}


void make_toolbar (QMenuBar *tool_bar, Window *graph_area, QMainWindow *window)
{
  QAction *action;

  action = tool_bar->addAction ("Change func", graph_area, SLOT (change_func ()));
  action->setShortcut (QString ("0"));
  action = tool_bar->addAction ("Change dispay", graph_area, SLOT (change_graph ()));
  action->setShortcut (QString ("1"));

  action = tool_bar->addAction ("Zoom in", graph_area, SLOT (zoom_in ()));
  action->setShortcut (QString ("2"));
  action = tool_bar->addAction ("Zoom out", graph_area, SLOT (zoom_out ()));
  action->setShortcut (QString ("3"));

  action = tool_bar->addAction ("Double n", graph_area, SLOT (double_n ()));
  action->setShortcut (QString ("4"));
  action = tool_bar->addAction ("Half n", graph_area, SLOT (half_n ()));
  action->setShortcut (QString ("5"));

  action = tool_bar->addAction ("Add delta", graph_area, SLOT (add_delta ()));
  action->setShortcut (QString ("6"));
  action = tool_bar->addAction ("Subtract delta", graph_area, SLOT (subtract_delta ()));
  action->setShortcut (QString ("7"));

  action = tool_bar->addAction ("Rotate Cl", graph_area, SLOT (rot_clock ()));
  action->setShortcut (Qt::Key_Left);
  action = tool_bar->addAction ("Rotate ACl", graph_area, SLOT (rot_unclock ()));
  action->setShortcut (Qt::Key_Right);

  action = tool_bar->addAction ("Rotate Up", graph_area, SLOT (rot_up ()));
  action->setShortcut (Qt::Key_Up);
  action = tool_bar->addAction ("Rotate Down", graph_area, SLOT (rot_down ()));
  action->setShortcut (Qt::Key_Down);

  action = tool_bar->addAction ("Exit", window, SLOT (close ()));
  action->setShortcut (QString ("Ctrl+X"));

  tool_bar->setFont (QFont("Arial", 5));
  tool_bar->setLayoutDirection (Qt::LeftToRight);

  tool_bar->setMaximumHeight (30);
  tool_bar->setStyleSheet("background-color: rgb(210, 185, 200); selection-background-color: rgb(150, 125, 140);");
}

void set_window (QMenuBar *tool_bar, Window *graph_area, QMainWindow *window)
{
  window->setMenuBar (tool_bar);
  window->setCentralWidget (graph_area);

  window->setWindowTitle ("Graph by Lobanova VA");
  window->setStyleSheet ("background-color: rgb(210, 185, 200); selection-background-color: rgb(48, 10, 36);");
}
