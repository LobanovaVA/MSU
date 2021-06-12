#include <stdio.h>

void 
f ()
{
  int c;
  scanf ("%d",  &c);

  if (c == 0)
  	return;

  if (c % 2 != 0)
  	printf("%d ", c);

  f ();
}

int
main (void)
{
  f();
  return 0;
}
