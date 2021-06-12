#include <stdio.h>

int
main (void)
{
  int n, i;
  scanf ("%d", &n);

  for (i = 2; i <= 9; i++)
    printf ("%d %d\n", i, (n - (n %i)) / i);
       
  return 0;
}
