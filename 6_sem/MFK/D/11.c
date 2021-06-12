#include <stdio.h>

int 
f (int n)
{
  if (n == 1)
  	return 1;

  return n % 2 + f (n / 2);
}

int
main (void)
{
  int n, i;
  scanf ("%d",  &n);

  if (n == 0)
  	return printf ("0\n"), 0;

  printf ("%d\n", f (n));
  return 0;
}
