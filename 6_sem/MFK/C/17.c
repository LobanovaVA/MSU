#include <stdio.h>

int 
is_happy_number (int n)
{
  long unsigned int sum = 0, prod = 1;

  if (n == 1 || n == 0)
    return 1;

  while (n != 0)
  {
    sum += n % 10;
    prod *= n % 10;

    n /= 10;
  }

  if (sum == prod)
    return 1;
  else 
    return 0;
}

int
main (void)
{
  int n, i, reminder;
  scanf ("%d", &n);
          
  if (is_happy_number  (n))
    printf ("YES\n");
  else 
    printf ("NO\n");

  return 0;
}
