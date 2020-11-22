#include "all_func.h"

// Problem 3_1
double
problem_3_1 (double a, double b, int n, int mode)
{
  int i;
  double h, s = 0, ans;
  h = (b - a) / n;

  for (i = 1; i < n; i++)
    s += f (a + i * h, mode);

  ans = h * f (a, mode) / 2 + h * s
      + h * f (b, mode) / 2;
  return ans;
}



// Problem 3_2
double
problem_3_2 (double a, double b, int n, int mode)
{
  int i;
  double h, s0 = 0, s1, ans;

  h = (b - a) / (2 * n);
  s1 = f (a + h, mode);

  for (i = 1; i < n; i++)
    {
      s0 += f (a + 2 * i * h, mode);
      s1 += f (a + (2 * i + 1) * h, mode);
    }

  ans = h * f (a, mode) / 3 + 2 * h * s0 / 3
      + 4 * h * s1 / 3 + h * f (b, mode) / 3;
  return ans;
}



// Problem 3_3
double
problem_3_3 (double a, double b, int n, int mode)
{
  int i;
  double h, s = 0, x1, x2, f1, f2;

  h = (b - a) / n;
  x1 = a;
  x2 = a + h;
  f1 = f (x1, mode);
  f2 = f (x2, mode);

  for (i = 0; i < n; i++)
    {
      s += integral_3 (x1, x2, f1, f2);
      f1 = f2;
      x1 = x2;
      x2 += h;
      f2 = f (x2, mode);
    }
  return s;
}

double
integral_3 (double x1, double x2, double f1, double f2)
{
  double a, b, sgn1, sgn2, ans;
  a = (f1 - f2) / (x1 - x2);
  b = (x1 * f2 - x2 * f1) / (x1 - x2);

  sgn1 = (x1 < 0) ? -1 : 1;
  sgn2 = (x2 < 0) ? -1 : 1;

  ans = (2./3) * a * ( fabs (x2) * sqrt (fabs (x2)) - fabs (x1) * sqrt (fabs (x1)) )
      + 2 * b * ( sgn2 * sqrt (fabs (x2)) - sgn1 * sqrt (fabs (x1)) );
  return ans;
}

// Problem 3_4
double
problem_3_4 (double a, double b, int n, int mode)
{
  int i;
  double h, s = 0, x1, x2, x3, f1, f2, f3;

  h = (b - a) / (2 * n);
  x1 = a;
  x2 = a + h;
  x3 = a + 2 * h;
  f1 = f (x1, mode);
  f2 = f (x2, mode);
  f3 = f (x3, mode);

  for (i = 0; i < n; i++)
    {
      s += integral_4 (x1, x2, x3, f1, f2, f3);
      x1 = x3;
      x2 += 2 * h;
      x3 += 2 * h;
      f1 = f3;
      f2 = f (x2, mode);
      f3 = f (x3, mode);
    }

  return s;
}


double
integral_4 (double x1, double x2, double x3, double f1, double f2, double f3)
{
  double  a, b, c, sgn1, sgn3, ans;

  a = ((f1 - f2) / (x1 - x2) - (f2 - f3) / (x2 - x3)) / (x1 - x3);

  b = (f1 - f2) / (x1 - x2) - (x1 + x2)
      * (((f1 - f2) / (x1 - x2) - (f2 - f3) / (x2 - x3)) / (x1 - x3));

  c = f1 - x1 * (f1 - f2) / (x1 - x2) + x1 * x2
      * (((f1 - f2) / (x1 - x2) - (f2 - f3) / (x2 - x3)) / (x1 - x3));

  sgn1 = (x1 < 0) ? -1 : 1;
  sgn3 = (x3 < 0) ? -1 : 1;

  x1 = fabs (x1);
  x3 = fabs (x3);
  ans = (2./5) * a * (x3 * x3 * sqrt (x3) - x1 * x1 * sqrt (x1))
      + (2./3) * b * (x3 * sqrt (x3) - x1 * sqrt (x1))
      + 2. * c * (sgn3 * sqrt (x3) - sgn1 * sqrt (x1));
  return ans;
}
