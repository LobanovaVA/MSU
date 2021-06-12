#include <stdio.h>
#include <math.h>

double
my_sinus (double x)
{
  double sum = x, fr = x;
  int  i = 2;
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
    ans = my_sinus(x);
  else 
    ans = 2 * my_sinus(x / 2) * (1 - 2 * (my_sinus(x / 4) * my_sinus(x / 4)));

  printf ("%.3f\n", ans);
  return 0;
}
