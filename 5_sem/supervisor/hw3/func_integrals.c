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

  ans = 0.5 * h * f (a, mode) + h * s
      + 0.5 * h * f (b, mode);
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

  ans = h * f (a, mode) / 3 + 2. * h * s0 / 3
      + 4. * h * s1 / 3 + h * f (b, mode) / 3;
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



// Problem 3_5
int problem_3_5 (double a, double b, double eps, double *r, int mode)
{
  int i, it, n = 1;
  double h, s, s2, sdop;

  h = fabs (b - a);
  s = 0.5 * h * f (a, mode) + 0.5 * h * f (b, mode);

  for (it = 0; it < MAX_IT_STEP; it++)
    {
      sdop = 0;
      for (i = 0; i < n; i++)
        sdop += f (a + (2 * i + 1) * h * 0.5, mode);

      s2 = 0.5 * (s + h * sdop);

      if (fabs (s2 - s) < eps)
        break;
      s = s2;
      h *= 0.5;
      n *= 2;
    }

  if (it >= MAX_IT_STEP)
    return ERROR_MAX_STEP;
  else
    {
      *r = s2;
      return 2 * n;
    }
}



// Problem 3_6
int problem_3_6 (double a, double b, double eps, double *r, int mode)
{
  int i, it, n = 1;
  double h, fa, fb, s_new, s1_new, s2_new, s1 = 0, s2, s;

  h = 0.5 * fabs (b - a);
  fa = f (a, mode);
  fb = f (b, mode);
  s2 = h * f (a + h, mode);
  s = h * fa / 3 + (4./3) * s2 + h * fb / 3;

  for (it = 0; it < MAX_IT_STEP; it++)
    {
      s1_new = 0.5 * (s1 + s2);
      s2_new = 0;

      for (i = 0; i < 2 * n; i++)
        s2_new += f (a + (2 * i + 1) * h * 0.5, mode);

      s2_new *= 0.5 * h;
      s_new = h * fa / 6 + (2./3) * s1_new + (4./3) * s2_new + h * fb / 6;

      if (fabs (s_new - s) < eps)
        break;

      s = s_new;
      s1 = s1_new;
      s2 = s2_new;
      h *= 0.5;
      n *= 2;
    }

  if (it >= MAX_IT_STEP)
    return ERROR_MAX_STEP;
  else
    {
      *r = s_new;
      return 2 * n;
    }
}



// Problem 3_7
int problem_3_7 (double a, double eps, double *r, int mode)
{
  int it, ret;
  double h = 1, b1, b2, s = 0, I;

  b1 = a;
  b2 = a + h;

  for (it = 0; it < MAX_IT; it++)
    {
      ret = integral_7 (b1, b2, eps, &I, mode);

      if (ret < 0)
        return ret;

      if (fabs (I) < eps)
        break;

      s += I;
      h *= 2;
      b1 = b2;
      b2 += h;
    }

  if (it >= MAX_IT)
    return ERROR_MAX_ITERATION;
  else
    {
      *r = s;
      return it;
    }
}


int integral_7 (double a, double b, double eps, double *r, int mode)
{
  int i, it, n = 1;
  double h, s, s2, sdop;

  h = fabs (b - a);
  s = 0.5 * h * (f (a, mode) + f (b, mode));

  for (it = 0; it < MAX_STEP; it++)
    {
      sdop = 0;
      for (i = 0; i < n; i++)
        sdop += f (a + (2 * i + 1) * h * 0.5, mode);

      s2 = 0.5 * (s + h * sdop);

      if (fabs (s2 - s) < eps)
        break;

      s = s2;
      h *= 0.5;
      n *= 2;
    }

  if (it >= MAX_STEP)
    return ERROR_MAX_STEP;
  else
    {
      *r = s2;
      return 2 * n;
    }
}



// Problem 3_8
int problem_3_8 (double a, double eps, double *r, int mode)
{
  int it, ret;
  double h = 1, b1, b2, s = 0, I;

  b1 = a;
  b2 = a + h;

  for (it = 0; it < MAX_IT; it++)
    {
      ret = integral_8 (b1, b2, eps, &I, mode);

      if (ret < 0)
        return ret;

      if (fabs (I) < eps)
        break;

      s += I;
      h *= 2;
      b1 = b2;
      b2 += h;
    }

  if (it >= MAX_IT)
    return ERROR_MAX_ITERATION;
  else
    {
      *r = s;
      return it;
    }
}

int integral_8 (double a, double b, double eps, double *r, int mode)
{
  int i, it, n = 1;
  double h, fa, fb, s_new, s1_new, s2_new, s1 = 0, s2, s;

  h = fabs (b - a) * 0.5;
  fa = f (a, mode);
  fb = f (b, mode);
  s2 = h * f (a + h, mode);
  s = h * fa / 3 + (4./3) * s2 + h * fb / 3;

  for (it = 0; it < MAX_STEP; it++)
    {
      s1_new = 0.5 * (s1 + s2);
      s2_new = 0;

      for (i = 0; i < 2 * n; i++)
        s2_new += f (a + (2 * i + 1) * h * 0.5, mode);

      s2_new *= 0.5 * h;
      s_new = h * fa / 6 + (2./3) * s1_new + (4./3) * s2_new + h * fb / 6;

      if (fabs (s_new - s) < eps)
        break;

      s = s_new;
      s1 = s1_new;
      s2 = s2_new;
      h *= 0.5;
      n *= 2;
    }

  if (it >= MAX_STEP)
    return ERROR_MAX_STEP;
  else
    {
      *r = s_new;
      return 2 * n;
    }
}



// Problem 3_9
int problem_3_9 (double a, double b, double eps, double *r, int mode)
{

  int i, it, n = 1;
  double h, s2, x1, x2, y1, y2, xa, xb, ya, yb, s;

  h = fabs (b - a);
  xa = x (a, mode);
  xb = x (b, mode);
  ya = y (a, mode);
  yb = y (b, mode);
  s = sqrt ((xa - xb) * (xa - xb) + (ya - yb) * (ya - yb));

  for (it = 0; it < MAX_STEP; it++)
    {
      s2 = 0;
      x1 = xa;
      y1 = ya;

      for (i = 1; i < 2 * n; i++)
        {
          x2 = x (a + i * h * 0.5, mode);
          y2 = y (a + i * h * 0.5, mode);
          s2 += sqrt ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
          x1 = x2;
          y1 = y2;
        }

      s2 += sqrt ((x1 - xb) * (x1 - xb) + (y1 - yb) * (y1 - yb));
      if (fabs (s2 - s) < eps)
        break;

      s = s2;
      h *= 0.5;
      n *= 2;
    }

  if (it >= MAX_STEP)
    return ERROR_MAX_STEP;
  else
    {
      *r = s2;
      return 2*n;
    }
}
