#include <stdio.h>

int 
is_prime (int n)
{
  int i;

  if (n == 1 || n== 0)
    return 0;

  for (i = 2; i < n; i++)
  {
    if (n % i == 0)
      return 0;
  }

  return 1;
}

int
main (void)
{
  int n, i, reminder;
  scanf ("%d", &n);
          
  if (is_prime (n))
    printf ("YES\n");
  else 
    printf ("NO\n");

  return 0;
}
