#include <stdio.h>

int 
my_middle (int a, int b)
{
  return (a + b) / 2;
}

int
main (void)
{
  int a, b;
  scanf ("%d %d", &a, &b);

  printf ("%d\n", my_middle (a, b));

  return 0;
}
