#include <stdio.h>

int
main (void)
{
  int a, b, i, sum = 0;
  scanf ("%d %d", &a, &b);

  for (i = a; i <= b; i++)
      sum += i * i;
      
  printf ("%d\n", sum);

  return 0;
}
