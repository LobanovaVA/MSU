#include <stdio.h>

void
f (int n)
{
  if (n == 0)
  	return;

  printf ("%d ", n);
  return f (n - 1);
}

int
main (void)
{
  int n, i;
  scanf ("%d",  &n);

  f (n);

  return 0;
}
