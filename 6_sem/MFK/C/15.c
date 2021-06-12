#include <stdio.h>

int 
grow_up (int n)
{
  int reminder;
  
  if (n < 0)
    n *= (-1);
    
  reminder = n % 10;
  n /= 10;
  
  for (; n > 0;  n /= 10)
    {
      if (reminder <= n % 10)
        return 0;
        
      reminder = n % 10; 
    }

  return 1;
}

int
main (void)
{
  int n, i, reminder;
  scanf ("%d", &n);
          
  if (grow_up (n))
    printf ("YES\n");
  else 
    printf ("NO\n");

  return 0;
}
