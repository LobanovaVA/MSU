#include <stdio.h>

int
main (void)
{
  int i, min, max, elem;
  scanf ("%d", &min);
  max = min;

  for (i = 1; i < 5; i++)
  {
  	scanf ("%d", &elem);
  	if (elem < min)
  	  min = elem;
    if (elem > max)
      max = elem;
  }

  printf("%d\n", max + min);
  return 0;
}
