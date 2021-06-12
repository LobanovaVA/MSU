#include <stdio.h>

long unsigned int 
my_num (int n, int p)
{
  long unsigned int ans = 0, d;
  int mod;

  for (d = 1; n >= p; d *= 10)
  {
    mod = n % p;
    ans += mod * d;
    n /= p;
  }

  ans += n * d;
  return ans;
}

int
main (void)
{
  int n, p;
  scanf ("%d %d", &n, &p);

  printf ("%lu\n", my_num (n, p));

  return 0;
}
