#include <stdio.h>

int 
is2pow (int n)
{

  if (n == 1 || n == 0)
    return 1;

  if (n % 2 != 0)
    return 0;

  return is2pow (n / 2);
}

int
main (void)
{
  int n, i, reminder;
  scanf ("%d", &n);
          
  if (is2pow (n))
    printf ("YES\n");
  else 
    printf ("NO\n");

  return 0;
}
