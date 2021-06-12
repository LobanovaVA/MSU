#include <stdio.h>

int
main (void)
{
  int n, i, j, reminder, tmp;
  scanf ("%d", &n);
  
  if (n < 0)
    n *= (-1);
      
  for (reminder = n % 10; n > 0; n /= 10, reminder = n % 10)
    {
      tmp = n / 10;
      for (j = tmp % 10; tmp > 0; tmp /= 10, j = tmp % 10)
        {
          if (reminder == j)
            {
              printf ("YES\n");
              return 0;
            }
        }
    }
          
  printf ("NO\n");
  return 0;
}
