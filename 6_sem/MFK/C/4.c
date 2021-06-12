#include <stdio.h>

int 
my_f (int x)
{
  if (x >= 2)
  	return x * x + 4 * x + 5;
  if (x < -2)
  	return 4;

  return x * x;
}

int
main (void)
{
  int n, max, ans;
  scanf ("%d", &n);
  max  = my_f (n);

  while (n != 0)
  {
  	ans = my_f (n);
  	if (ans > max) 
      max = ans;

  	scanf ("%d", &n);

  }

  printf ("%d\n", max);
  return 0;
}
