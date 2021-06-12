#include <stdio.h>

int 
check_br (char c)
{
  if (c == '(')
    return 1;
  else 
    return -1;
}

int
main (void)
{
  int count = 0;
  char c;
  scanf ("%c", &c);

  while (c != '.')
  {
    count += check_br (c);
    if (count < 0)
      return printf ("NO\n"), 0;

    scanf ("%c", &c);
  }

  if (count == 0)
    printf ("YES\n");
  else
    printf ("NO\n");
  return 0;
}
