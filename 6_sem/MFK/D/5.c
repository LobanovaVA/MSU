#include <stdio.h>

int 
f (int n)
{
  if (n == 1)
  	return printf("1");

  f (n / 2);
  printf("%d", n % 2);
}

int
main (void)
{
  int n, i;
  scanf ("%d",  &n);

  if (n == 0)
  	return printf ("0\n"), 0;

  f (n);
  return 0;
}
