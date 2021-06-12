#include <stdio.h>

int
main (void)
{
  int a, b;
  scanf ("%d %d", &a, &b);

  if (a > b)
    return printf("Above\n"), 0;

  if (b > a)
    return printf("Less\n"), 0;

  return printf("Equal\n"), 0;
}
