#include <stdio.h>

int 
is_prime (int n, int delitel)
{

  if (n == 1 || n == 0)
    return 0;

  if (n == delitel)
    return 1;

  if (n % delitel == 0)
    return 0;

  return is_prime (n, delitel + 1);
}

int
main (void)
{
  int n, i, reminder;
  scanf ("%d", &n);
          
  if (is_prime (n, 2))
    printf ("YES\n");
  else 
    printf ("NO\n");

  return 0;
}
