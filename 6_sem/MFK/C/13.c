#include <stdio.h>
#include <math.h>

double
my_cosin (double x)
{
  double sum = 1., fr = 1.;
  int  i = 1;
  while (fabs(fr) > 0.001 )
  {
    //fr *= (-1.0)  * (x / i) * (x / (i + 1));
    fr *= (-1.0) * x * x / (i * (i + 1));
    sum += fr;
    i += 2;
  }

  return sum;
}


int
main (void)
{
  int n;
  double ans, x;

  scanf ("%d", &n);

  x = n * M_PI / 180;
  if (x < 1)
    ans = my_cosin(x);
  else 
    ans = 2 * my_cosin(x / 2) * my_cosin(x / 2) - 1;

  printf ("%.3f\n", fabs(ans));
  return 0;
}
