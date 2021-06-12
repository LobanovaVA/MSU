#include <stdio.h>

int
main (void)
{
  int a, b, c;
  scanf ("%d %d %d",  &a, &b, &c);

  double mean;
  mean = (a + b + c) / 3.0;
  
  printf("%.2f\n", mean);
  return 0;
}
