#include <stdio.h>

int 
my_abs (int n)
{
  if (n < 0)
  	return -n;
  else 
  	return n;
}

int
main (void)
{
  int n, i;
  scanf ("%d",  &n);

  printf ("%d\n", my_abs (n));

  return 0;
}
