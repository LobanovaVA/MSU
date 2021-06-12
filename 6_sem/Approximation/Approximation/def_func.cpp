#include "def_func.h"
#include "window.h"

void
def_func::set_f0 (Window *graph_area)
{
  graph_area -> f_name = "f (x) = 1";
  graph_area -> f = f_0;
  graph_area -> ddf = ddf_0;
}

void
def_func::set_f1 (Window *graph_area)
{
  graph_area -> f_name = "f (x) = x";
  graph_area -> f = f_1;
  graph_area -> ddf = ddf_1;
}

void
def_func::set_f2 (Window *graph_area)
{
  graph_area -> f_name = "f (x) = x^2";
  graph_area -> f = f_2;
  graph_area -> ddf = ddf_2;
}

void
def_func::set_f3 (Window *graph_area)
{
  graph_area -> f_name = "f (x) = x^3";
  graph_area -> f = f_3;
  graph_area -> ddf = ddf_3;
}

void
def_func::set_f4 (Window *graph_area)
{
  graph_area -> f_name = "f (x) = x^4";
  graph_area -> f = f_4;
  graph_area -> ddf = ddf_4;
}

void
def_func::set_f5 (Window *graph_area)
{
  graph_area -> f_name = "f (x) = exp(x)";
  graph_area -> f = f_5;
  graph_area -> ddf = ddf_5;

  if (std::max (std::abs (graph_area -> a), std::abs (graph_area -> b)) > EXP_LIM)
    {
      print_message (Message_type::information, "Autoupdate arguments",
                     "Big arguments for exp.\nUsed max [%d; %d].\nReset:\n  a = %4.d\n  b = %4.d",
                     -EXP_LIM, EXP_LIM, DEFAULT_A, DEFAULT_B);

      graph_area -> a = -10;
      graph_area -> b = 10;
    }
}

void
def_func::set_f6 (Window *graph_area)
{
  graph_area -> f_name = "f (x) = 1 / (25*x^2 + 1)";
  graph_area -> f = f_6;
  graph_area -> ddf = ddf_6;
}
