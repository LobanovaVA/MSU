#include <stdio.h>

int
main (void)
{
  int n, i, reminder;
  scanf ("%d", &n);
  
  if (n < 0)
    n *= (-1);
    
  reminder = n % 10;
  n /= 10;
  
  for (; n > 0;  n /= 10)
    {
      if (reminder <= n % 10)
        {
          printf ("NO\n");
          return 0;
        }
       
      reminder = n % 10; 
    }
          
  printf ("YES\n");
  return 0;
}
