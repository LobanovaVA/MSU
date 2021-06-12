#include <stdio.h>

 void
f (int n)
{
  if (n == 0)
  	return;

  printf ("%d ", n % 10);
  return f (n / 10);

}

int
main (void)
{
  int n, i;
  scanf ("%d",  &n);

  if (n == 0)
  	printf ("%d\n", n);

  f (n);

  return 0;
}
