#include <stdio.h>

char
my_edit (char x)
{
  if (x >= 'a' && x <= 'z')
    x = (x - '0' - 32) + '0';

  return x;
}

int
main (void)
{
  char c;
  scanf ("%c", &c);

  while (c != '.')
  {
    printf ("%c", my_edit (c));
    scanf ("%c", &c);

  }

  return 0;
}
