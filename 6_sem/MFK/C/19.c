#include <stdio.h>

int 
digit_to_num (char c)
{
  if (c >= '0' && c <= '9')
    return c - '0';

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
    count += digit_to_num (c);
    scanf ("%c", &c);
  }

  printf ("%d\n", count);
  return 0;
}
