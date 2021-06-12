#include <stdio.h>

long unsigned int 
my_num_fact (unsigned int n)
{
  long unsigned int i, fact = 1;
  for (i = 1; i <= n; i++)
    fact *= i;

  return fact;
}

int
main (void)
{
  int n;
  scanf ("%d", &n);

  printf ("%lu\n", my_num_fact (n));
  return 0;
}
