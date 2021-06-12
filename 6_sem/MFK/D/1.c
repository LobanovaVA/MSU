#include <stdio.h>

 void
f (int i, int n)
{
  if (i > n)
  	return;

  printf ("%d ", i);
  return f (i + 1, n);
}

int
main (void)
{
  int n;
  scanf ("%d",  &n);

  f (1, n);

  return 0;
}
