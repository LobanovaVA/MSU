#include <stdio.h>

void
f (int n)
{
  if (n == 0)
    return;

  f (n / 10);

  if (n % 2 == 0) 
  	printf ("%d ", n % 10);
}

int
main (void)
{
  int n;
  scanf ("%d",  &n);

  if (n == 0)
  	printf ("0\n");

  f (n);

  return 0;
}
