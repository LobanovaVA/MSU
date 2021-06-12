#include <stdio.h>

int
main (void)
{
  int i, a, b;
  scanf ("%d", &a);

  for (i = 1; i < 5; i++)
  {
  	scanf ("%d", &b);
  	if (b < a)
  	  a = b;
  }

  printf("%d\n", a);
  return 0;
}
