#include "all_func.h"

// Problem 2_1
int
problem_2_1 (double a, double b, double eps, double *x, int mode)
{
  int it = 0;
  double c, fa, fb, fc;

  fa = f (a, mode);
  fb = f (b, mode);

  if (fa * fb > 0)
    return ERROR_NO_SOLUTION;

  if (fabs (fa) < eps)
    {
      *x = a;
      return it;
    }

  if (fabs (fb) < eps)
    {
      *x = b;
      return it;
    }

  for (it = 1; it < MAX_IT; it++)
    {
      c = (a + b) / 2;
      if (!(a > c || a < c))
        break;

      fc = f (c, mode);
      if (fabs (fc) < eps)
        break;

      if (fa * fc < 0)
        {
          b = c;
          fb = fc;
        }
      else
        {
          a = c;
          fa = fc;
        }

      if (fabs (b-a) < eps)
        break;
    }

  if (it >= MAX_IT)
    return ERROR_MAX_ITERATION;
  else
    {
      *x = c;
      return it;
    }
}



// Problem 2_2
int
problem_2_2 (double x0, double eps, double *x, int mode)
{
  int it = 0;
  double c, fx0, dx0;

  fx0 = f (x0, mode);
  dx0 = d (x0, mode);

  if (fabs (fx0) < eps)
    {
      *x = x0;
      return it;
    }

  for (it = 1; it < MAX_IT; it++)
    {
      if (!(dx0 > 0 || dx0 < 0))
        return ERROR_NO_SOLUTION;
      //      if (fabs (dx0) < EPS)
      //        return ERROR_NO_SOLUTION;

      c = x0 - fx0 / dx0;
      if (!(x0 > c || x0 < c))
        break;

      x0 = c;
      fx0 = f (c, mode);
      dx0 = d (c, mode);

      if (fabs (fx0) < eps)
        break;
    }

  if (it >= MAX_IT)
    return ERROR_MAX_ITERATION;
  else
    {
      *x = c;
      return it;
    }
}



// Problem 2_3
int
problem_2_3 (double a, double b, double eps, double *x, int mode)
{
  int it = 0;
  double c, fa, fb, fc;

  fa = f (a, mode);
  fb = f (b, mode);

  if (fa * fb > 0)
    return ERROR_NO_SOLUTION;

  if (fabs (fa) < eps)
    {
      *x = a;
      return it;
    }

  if (fabs (fb) < eps)
    {
      *x = b;
      return it;
    }

  for (it = 1; it < MAX_IT; it++)
    {
      c = (fb * a - fa * b) / (fb - fa);
      if (!(a > c || a < c) || !(b > c || b < c))
        break;

      fc = f (c, mode);
      if (fabs (fc) < eps)
        break;

      if (fa * fc < 0)
        {
          b = c;
          fb = fc;
        }
      else
        {
          a = c;
          fa = fc;
        }

      if (fabs (b-a) < eps)
        break;
    }

  if (it >= MAX_IT)
    return ERROR_MAX_ITERATION;
  else
    {
      *x = c;
      return it;
    }
}



// Problem 2_4
int
problem_2_4 (double a, double b, double eps, double *x, int mode)
{
  int it = 0;
  double c, fa, fb, fc;

  fa = f (a, mode);
  fb = f (b, mode);

  if (fa * fb > 0)
    return ERROR_NO_SOLUTION;

  if (fabs (fa) < eps)
    {
      *x = a;
      return it;
    }

  if (fabs (fb) < eps)
    {
      *x = b;
      return it;
    }

  for (it = 1; it < MAX_IT; it++)
    {
      if (!(fa > fb || fa < fb))
        return ERROR_NO_SOLUTION_M4_1;

      c = (fb * a - fa * b) / (fb - fa);
      if (!(a > c || a < c) || !(b > c || b < c))
        break;

      fc = f (c, mode);
      if (fabs (fc) < EPS)
        break;

      if (fabs (fc) > fabs(fa) && fabs (fc) > fabs (fb))
        return ERROR_NO_SOLUTION_M4_2;
      else
        {
          if (!(fabs (fb) < fabs(fa)))
            {
              b = c;
              fb = fc;
            }
          else
            {
              a = c;
              fa = fc;
            }
        }

      if (fabs (b - a) < eps)
        break;
    }

  if (it >= MAX_IT)
    return ERROR_MAX_ITERATION;
  else
    {
      *x = c;
      return it;
    }
}



// Problem 2_5
int
problem_2_5 (double a, double b, double eps, double *x, int mode)
{
  int it = 0, i, j;
  double c, d, fa, fb, fc, fd;
  double y[3], m[3];

  c = (a + b) / 2;
  if (!(a > c || a < c))
    {
      *x = c;
      return it;
    }

  fa = f (a, mode);
  fb = f (b, mode);
  fc = f (c, mode);

  //  if (fa * fb > 0)
  //    return ERROR_NO_SOLUTION;

  if (fabs (fa) < eps)
    {
      *x = a;
      return it;
    }

  if (fabs (fb) < eps)
    {
      *x = b;
      return it;
    }

  if (fabs (fc) < eps)
    {
      *x = c;
      return it;
    }

  for (it = 1; it < MAX_IT; it++)
    {
      y[0] = fa;
      y[1] = fb;
      y[2] = fc;
      m[0] = a;
      m[1] = b;
      m[2] = c;

      for (i = 1; i < 3; i++)
        for (j = 2; j >= i; j--)
          m[j] = ( m[j - 1] * y[j] - m[j] * y[j - i] ) / (y[j] - y[j - i]);

      //      d = y[0] + (0 - x[0]) * (y[0] - y[1]) / (x[0] - x[1]) + (0 - x[0]) * (0 - x[1])
      //               * ( (y[0] - y[1]) / (x[0] - x[1]) - (y[1] - y[2]) / (x[1] - x[2]) ) / (x[0] - x[2]);

      d = m [2];
      fd = f (d, mode);
      if (fabs (fd) < eps)
        break;

      if (fabs (fd) > fabs (fa) && fabs (fd) > fabs (fb) && fabs (fd) > fabs (fc))
        return ERROR_NO_SOLUTION_M5_1;
      else
        {
          if (fabs (fc) > fabs (fa) && fabs (fc) > fabs (fb) && fabs (fc) > fabs (fd))
            {
              c = d;
              fc = fd;
            }
          else
            {
              if (fabs (fb) > fabs (fa) && fabs (fb) > fabs (fc) && fabs (fb) > fabs (fd))
                {
                  b = d;
                  fb = fd;
                }
              else
                {
                  if (fabs (fa) > fabs (fb) && fabs (fa) > fabs (fc) && fabs (fa) > fabs(fd))
                    {
                      a = d;
                      fa = fd;
                    }
                  else
                    return ERROR_NO_SOLUTION_M5_2;
                }
            }
        }
    }

  if (it >= MAX_IT)
    return ERROR_MAX_ITERATION;
  else
    {
      *x = d;
      return it;
    }
}




// Problem 2_7
int problem_2_7 (double x0, double eps, double *x, int mode)
{
  int it = 0;
  double c;

  for (it = 1; it < MAX_IT; it++)
    {
      c = f (x0, mode);

      if (mode == 4 && x0 < 0)
        return ERROR_NO_SOLUTION;

      if (fabs (c - x0) < eps)
        break;
      x0 = c;
    }

  if (it >= MAX_IT)
    return ERROR_MAX_ITERATION;
  else
    {
      *x = c;
      return it;
    }
}



// Problem 2_8
int
problem_2_8 (double a, double b, double eps, double *x, int mode)
{
  int it = 0;
  double h, x0, x1, f0, f1;

  h = (b - a) / 10;
  x0 = a;
  f0 = f (x0, mode);
  if (mode == 4 && x0 < 0)
    return ERROR_NO_SOLUTION;

  for (it = 1; it < MAX_IT; it++)
    {
      if (fabs (h) < eps)
        break;

      x1 = x0 + h;
      f1 = f (x1, mode);
      if (mode == 4 && x1 < 0)
        return ERROR_NO_SOLUTION;

      if (!(x1 < b))
        {
          x1 = b;
          h /= (-10);
        }

      if (!(x1 > a))
        {
          x1 = a;
          h /= (-10);
        }

      if (f0 > f1)
        h /= (-10);

      x0 = x1;
      f0 = f1;
    }

  if (it >= MAX_IT)
    return ERROR_MAX_ITERATION;
  else
    {
      *x = f0;
      return it;
    }
}



// Problem 2_9
int
problem_2_9 (double a, double b, double eps, double *x, int mode)
{
  int it = 0;
  double fa, fb, s;

  fa = f (a, mode);
  if (mode == 4 && a < 0)
    return ERROR_NO_SOLUTION;

  fb = f (b, mode);
  if (mode == 4 && b < 0)
    return ERROR_NO_SOLUTION;

  s= (sqrt (5) + 1) * 0.5;

  for (it = 1; it < MAX_IT; it++)
    {
      if (fabs (b - a) < eps)
        break;
      if (fa < fb)
        {
          a = a + (b - a) / s;
          fa=f(a, mode);
          if (mode == 4 && a < 0)
            return ERROR_NO_SOLUTION;

        }
      else
        {
          b = b - (b - a) / s;
          fb = f (b, mode);
          if (mode == 4 && b < 0)
            return ERROR_NO_SOLUTION;

        }
    }

  if (it >= MAX_IT)
    return ERROR_MAX_ITERATION;
  else
    {
      *x = fb;
      return it;
    }
}



// Problem 2_10
int
problem_2_10 (double a, double b, double eps, double *x, int mode)
{
  int it = 0, i, imax = 0, imin = 0;
  double c, d, fa, fb, fc, fd, ka, kb, m[6], max, min;

  c = (b + a) / 2;
  fa = f (a, mode);
  fb = f (b, mode);
  fc = f (c, mode);

  m[0] = a;
  m[1] = b;
  m[2] = c;
  m[3] = fa;
  m[4] = fb;
  m[5] = fc;

  for (it = 1; it < MAX_IT; it++)
    {
      ka = ( ((m[3] - m[4]) / (m[0] - m[1])) - ((m[4] - m[5]) / (m[1] - m[2])) ) / (m[0] - m[2]);
      kb = ((m[3] - m[4]) / (m[0] - m[1])) - (m[0] + m[1])
          * ( ( ((m[3] - m[4]) / (m[0] - m[1])) - ((m[4] - m[5]) / (m[1] - m[2])) ) / (m[0] - m[2]) );

      if (ka > 0)
        return ERROR_NO_SOLUTION;

      d = (-0.5) * kb / ka;
      fd = f(d, mode);

      max = m[3];
      min = m[3];

      for (i = 3; i < 6; i++)
        {
          if (m[i] > max)
            {
              max = m[i];
              imax = i - 3;
            }
          if (m[i] < min)
            {
              min = m[i];
              imin = i - 3;
            }
        }

      m[imin] = d;
      m[imin + 3] = fd;

      if (fabs (fd - m[imax + 3]) < eps || fabs (d - m[imax]) < eps)
        break;
    }

  if (it >= MAX_IT)
    return ERROR_MAX_ITERATION;
  else
    {
      *x = fd;
      return it;
    }
}

