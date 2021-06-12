#include <stdio.h>

int 
f (int n)
{
  if (n == 0)
  	return 0;

  return n % 10 + f (n / 10);
}

int
main (void)
{
  int n, i;
  scanf ("%d",  &n);

  printf ("%d\n", f (n));

  return 0;
}
