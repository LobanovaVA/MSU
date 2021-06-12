#include <stdio.h>

int 
akkerman (int m, int n)
{
  if (m == 0)
  	return n + 1;

  if (n == 0)
  	return akkerman (m - 1, 1);

  return akkerman (m - 1, akkerman (m, n -1));
}

int
main (void)
{
  int n, m;
  scanf ("%d %d",  &m, &n);

  printf ("%d\n", akkerman (m, n));
  return 0;
}
