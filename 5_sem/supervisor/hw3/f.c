#include "all_func.h"

double
f (double x, int mode)
{
  double value = 0;
  switch (mode)
    {
    case 1:
      value = x;
      break;
    case 2:
      value = 1 - x * x;
      break;
    case 3:
      value =  x * x * x - 2 * x * x + x;
      break;
    case 4:
      if (!(x < 0))
        value = sqrt (x) - 3;
      else
        printf ("WARNING: cannot apply f-formula %d for x = %f\n", mode, x);
      break;
    case 5:
      value = 1. / (x * x + 1);
      break;
    default:
      printf ("Unknown parameter %d for f\n", mode);
    }
  return value;
}


double
d (double x, int mode)
{
  double value = 0;
  switch (mode)
    {
    case 1:
      value = 1;
      break;
    case 2:
      value = -2 * x;
      break;
    case 3:
      value = 3 * x * x - 4 * x + 1;
      break;
    case 4:
      if (!(x < 0))
        value = 1 / (2 * sqrt (x));
      else
        printf ("WARNING: cannot apply d-formula %d for x = %f\n", mode, x);
      break;
    case 5:
      value = (-2 * x) / ((x * x + 1) * (x * x + 1));
      break;
    default:
      printf ("Unknown parameter %d for d\n", mode);
    }
  return value;
}


double
x (double t, int mode)
{
  double value = 0;
  switch (mode)
    {
    case 1:
      value = t;
      break;
    case 2:
      value = t;
      break;
    case 3:
      value =  t;
      break;
    case 4:
      value =  t;
      break;
    case 5:
      value =  t;
      break;
    case 6:
      value = cos (t);
      break;
    default:
      printf ("Unknown parameter %d for x\n", mode);
    }
  return value;
}



double
y (double t, int mode)
{
  double value = 0;
  switch (mode)
    {
    case 1:
      value = t;
      break;
    case 2:
      value = 1 - t * t;
      break;
    case 3:
      value =  t * t * t - 2 * t * t + t;
      break;
    case 4:
      if (!(t < 0))
        value = sqrt (t) - 3;
      else
        printf ("WARNING: cannot apply y-formula %d for x = %f\n", mode, t);
      break;
    case 5:
      value = 1. / (t * t + 1);
      break;
    case 6:
      value = sin (t);
      break;
    default:
      printf ("Unknown parameter %d for y\n", mode);
    }
  return value;
}
