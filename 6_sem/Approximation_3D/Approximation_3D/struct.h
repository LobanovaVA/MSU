#ifndef STRUCT_H
#define STRUCT_H

#include <cmath>
#include <string>
#include <vector>


struct thread_info; //не компл если убрать

struct input_info
{
  char *file_name;
  int nx;
  int ny;
  int f_k;
  int th_p;
  double eps;
};

struct point_2d
{
  double x = 0;
  double y = 0;

  point_2d () = default;
  point_2d (double x_, double y_) { x = x_; y = y_; }

  point_2d &operator + (point_2d &a)
  {
    x += a.x;
    y += a.y;
    return *this;
  }
};

struct point_3d
{
  double x = 0;
  double y = 0;
  double z = 0;

  point_3d () = default;
  point_3d (double x_, double y_, double z_) { x = x_; y = y_; z = z_; }
};

struct polygon
{
  point_2d UL; /* up left */
  point_2d DR; /* down right */

  polygon () = default;
  polygon (point_2d x, point_2d y) { UL = x; DR = y; }
};

struct triangle_ind
{
  int a = 0;
  int b = 0;
  int c = 0;

  triangle_ind () = default;
  triangle_ind (int a_, int b_, int c_) { a = a_; b = b_; c = c_; }
};

struct triangle
{
  std::pair <point_2d, int> a;
  std::pair <point_2d, int> b;
  std::pair <point_2d, int> c;
  bool border = false;
  bool singular = false;
};

class def_func
{
public:
    static double f_0 (double  , double  ) { return 1; }
    static double f_1 (double x, double  ) { return x; }
    static double f_2 (double  , double y) { return y; }
    static double f_3 (double x, double y) { return x + y; }
    static double f_4 (double x, double y) { return sqrt (x * x + y * y); }
    static double f_5 (double x, double y) { return x * x + y * y; }
    static double f_6 (double x, double y) { return exp (x * x - y * y); }
    static double f_7 (double x, double y) { return 1 / (25 * (x * x + y * y) + 1); }

    std::string f_0_name = "1";
    std::string f_1_name = "x";
    std::string f_2_name = "y";
    std::string f_3_name = "x + y";
    std::string f_4_name = "sqrt (x^2 + y^2)";
    std::string f_5_name = "x^2 + y^2";
    std::string f_6_name = "exp (x^2 - y^2)";
    std::string f_7_name = "1 / (25(x^2 + y^2) + 1)";
};

struct minmax
{
  double max =  1;
  double min = -1;
};

struct solver_data
{
  std::vector<int> I;
  std::vector<double> A;

  std::vector<double> rhs;
  std::vector<double> x;

  std::vector<double> u;
  std::vector<double> r;
  std::vector<double> v;
  std::vector<double> buf;

  solver_data ()
  {
    I.reserve (6000000);
    A.reserve (6000000);

    rhs.reserve (1000000);
    x.reserve (1000000);

    u.reserve (1000000);
    r.reserve (1000000);
    v.reserve (1000000);

    buf.reserve (100);
  }

  void
  allocate_memory (int len, int size, int th_p)
  {
    I.resize (len);
    A.resize (len);

    rhs.resize (size);
    x.resize (size);

    u.resize (size);
    r.resize (size);
    v.resize (size);
    buf.resize (th_p);
  }

  void
  set_zero ()
  {
    std::fill (x.begin(), x.end(), 0);
    std::fill (u.begin(), u.end(), 0);
    std::fill (r.begin(), r.end(), 0);
    std::fill (v.begin(), v.end(), 0);
    std::fill (buf.begin(), buf.end(), 0);
  }
};

#endif // STRUCT_H
