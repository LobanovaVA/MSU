#include <stdio.h>

long unsigned int 
my_pow_2 (unsigned int n)
{
  long unsigned int i = 1, ans = 1;
  for (i = 1; i < n; i++)
    ans *= 2;

  return ans;
}

int
main (void)
{
  int n;
  scanf ("%d", &n);

  printf ("%lu\n", my_pow_2 (n));
  return 0;
}
