#include <stdio.h>

int
main (void)
{
  int n, i, reminder, min, max;
  scanf ("%d", &n);
    
  min = n % 10;
  max = n % 10;
  
  for (; n > 0;  n /= 10)
    {
     reminder = n % 10;
     
      if (max <= reminder)
        max = reminder;
      
      if (min > reminder)
        min = reminder;
    }
          
  printf ("%d %d\n", min, max);
  return 0;
}
