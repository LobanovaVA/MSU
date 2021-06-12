#include <stdio.h>

int 
my_pow (int n, int p)
{
  int i, ans = n;

  if (p == 0)
  	return 1;

  for (i = 1; i< p; i++)
  	ans *= n;

  return ans;
}

int
main (void)
{
  int n, p;
  scanf ("%d %d", &n, &p);

  printf ("%d\n", my_pow (n, p));

  return 0;
}
