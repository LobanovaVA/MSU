#include <stdio.h>

int
acounter ()
{
  char c;
  scanf ("%c",  &c);

  if (c == '.')
  	return 0;

  if (c == 'a')
  	return 1 + acounter ();

  return acounter ();
}

int
main (void)
{
  printf ("%d\n", acounter ());
  return 0;
}
