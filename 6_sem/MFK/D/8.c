#include <stdio.h>

void
f (int a, int b)
{

  printf ("%d ", a);

  if (a == b)
  	return;

  if (a > b)
  	a--;
  else 
  	a++;

  return f (a, b);
}

int
main (void)
{
  int a, b;
  scanf ("%d %d",  &a, &b);

  f (a, b);

  return 0;
}
