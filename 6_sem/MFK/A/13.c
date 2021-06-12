#include <stdio.h>

int
main (void)
{
  int i, a, mult = 1;
  scanf ("%d", &a);

  for (i = 0; i < 3; i++)
  {
    mult *= a % 10;
    a = a / 10;
  }

  printf("%d\n", mult);
  return 0;
}
