#ifndef DEF_FUNC_H
#define DEF_FUNC_H

#include <cmath>

#define EXP_LIM 39

class Window;

class def_func
{
public:
    static double f_0 (double)   { return 1; }
    static double f_1 (double x) { return x; }
    static double f_2 (double x) { return x * x; }
    static double f_3 (double x) { return x * x * x; }
    static double f_4 (double x) { return x * x * x * x; }
    static double f_5 (double x) { return exp (x); }
    static double f_6 (double x) { return 1 / (25 * x * x + 1); }

    static double ddf_0 (double)   { return 0; }
    static double ddf_1 (double)   { return 0; }
    static double ddf_2 (double)   { return 2; }
    static double ddf_3 (double x) { return 6 * x; }
    static double ddf_4 (double x) { return 12 * x * x; }
    static double ddf_5 (double x) { return exp (x); }
    static double ddf_6 (double x)
    {
      double tmp = 25 * x * x - 1;
      return 50 * (75 * x * x - 1) / (tmp * tmp * tmp);
    }

    void set_f0 (Window *graph_area);
    void set_f1 (Window *graph_area);
    void set_f2 (Window *graph_area);
    void set_f3 (Window *graph_area);
    void set_f4 (Window *graph_area);
    void set_f5 (Window *graph_area);
    void set_f6 (Window *graph_area);
};

#endif // DEF_FUNC_H
