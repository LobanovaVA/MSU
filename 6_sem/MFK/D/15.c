#include <stdio.h>

int 
max_find (int max)
{
  int c;
  scanf ("%d",  &c);

  if (c == 0)
  	return max;

  if (c > max)
  	max = c;

  return max_find (max);
}

int
main (void)
{
  int c;
  scanf ("%d",  &c);

  printf("%d\n", max_find (c));
  return 0;
}
