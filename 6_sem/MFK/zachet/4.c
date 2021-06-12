#include <stdio.h>

int check (int n);

int 
check (int n)
{
  int sum = 0;

  for (int i = 1; i <= n / 2; i++)
    if (n % i == 0)
      sum += i;

  if (n == sum)
    return 1;

  return 0;
}

int
main (void)
{
  int n;
  scanf ("%d", &n);
    
  while (n != 0)
  {
    if (check (n))
      printf ("%d ", n);

    scanf ("%d", &n);
  }
    
  return 0;
}
