#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QAction>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMessageBox>

#include "window.h"

void make_toolbar (QMenuBar *tool_bar, Window *graph_area, QMainWindow *window);
void set_window (QMenuBar *tool_bar, Window *graph_area, QMainWindow *window);

int main (int argc, char *argv[])
{
  QApplication app (argc, argv);

  QMainWindow *window = new QMainWindow;
  QMenuBar *tool_bar = new QMenuBar (window);
  Window *graph_area = new Window (window);

  if (graph_area->parse_command_line (argc, argv))
    {
      print_message (Message_type::warning, "Wrong input arguments!",
                     "Use any of the options:\n  ./a.out a b [n > 0] [k = 0..6]\n  "
                     "./a.out a b [n > 0]\n  ./a.out a b\n  ./a.out\n  where b - a < 1.e-6",
                     argv[0]);
      return -1;
    }

  make_toolbar (tool_bar, graph_area, window);
  set_window (tool_bar, graph_area, window);

  window->show ();
  app.exec ();

  delete graph_area;
  delete tool_bar;
  delete window;

  return 0;
}


void make_toolbar (QMenuBar *tool_bar, Window *graph_area, QMainWindow *window)
{
  QAction *action;

  action = tool_bar->addAction ("Change function", graph_area, SLOT (change_func ()));
  action->setShortcut (QString ("0"));
  action = tool_bar->addAction ("Change dispaled graphs", graph_area, SLOT (change_graph ()));
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

  QMenu *set_args;

  set_args = tool_bar->addMenu("Set your arguments");
  set_args->setFont (QFont("Arial", 5));
  set_args->addAction("Set n = 1e7", graph_area, SLOT (set_n_10 ()));
  set_args->addAction("Set n", graph_area, SLOT (set_n_input ()));
  set_args->addAction("Set a", graph_area, SLOT (set_a_input ()));
  set_args->addAction("Set b", graph_area, SLOT (set_b_input ()));
  set_args->addAction("Set k", graph_area, SLOT (set_k_input ()));

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
  window->setStyleSheet("background-color: rgb(210, 185, 200); selection-background-color: rgb(48, 10, 36);");
}
