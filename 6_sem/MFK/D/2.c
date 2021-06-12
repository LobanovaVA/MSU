#include <stdio.h>

int 
f (int i, int n)
{
  if (i > n)
  	return 0;

  return i + f (i + 1, n);
}

int
main (void)
{
  int n, i;
  scanf ("%d",  &n);

  printf ("%d\n", f (1, n));
  return 0;
}
