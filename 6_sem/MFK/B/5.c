#include <stdio.h>

int
main (void)
{
  int n, i, sum = 0;
  scanf ("%d", &n);
  
  if (n < 0)
    n *= (-1);
  
  for (i = 0; n > 0; i++)
    {
      sum += n % 10;
      n /= 10; 
    }
          
  printf ("%d\n", sum);
  return 0;
}
