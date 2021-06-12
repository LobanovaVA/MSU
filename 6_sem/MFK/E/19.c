#include <stdio.h>

int
main (void)
{
  int n, N;
  long unsigned int i;

  scanf ("%d", &n);
  N = n;

  for (i = 1; n > 0; i *= 10, n /= 10);

  while (i > 1)
  {
  	i /= 10;
  	printf("%lu ", N / i);
  	N %= i;
  }
       
  return 0;
}
