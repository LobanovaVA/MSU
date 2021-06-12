#include <stdio.h>

int
main (void)
{
  int i, a, n;
  scanf ("%d", &a);
  n = a % 10;

  for (i = 0; i < 3; i++)
  {
    if (n < a % 10)
      n = a % 10;
    a = a / 10;
  }

  printf("%d\n", n);
  return 0;
}
