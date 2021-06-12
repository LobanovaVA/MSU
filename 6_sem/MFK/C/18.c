#include <stdio.h>

int 
is_digit (char c)
{
  if (c >= '0' && c <= '9')
    return 1;

  return 0;
}

int
main (void)
{
  int count = 0;
  char c;
  scanf ("%c", &c);

  while (c != '.')
  {
    count += is_digit (c);
    scanf ("%c", &c);
  }

  printf ("%d\n", count);
  return 0;
}
