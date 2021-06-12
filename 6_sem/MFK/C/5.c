#include <stdio.h>

int 
my_num_sum (int n)
{
  int i, sum = 0;;
  for (i = 1; i <= n; i++)
    sum += i;

  return sum;
}

int
main (void)
{
  int n;
  scanf ("%d", &n);

  printf ("%d\n", my_num_sum (n));
  return 0;
}
