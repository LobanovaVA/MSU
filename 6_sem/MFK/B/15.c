#include <stdio.h>

int
main (void)
{
  int n, i;
  scanf ("%d", &n);
    
  for (i = 0; n != 0;)
  {
    if (n % 2 == 0)
      i++;
      
    scanf ("%d", &n);
  }
    
  
  printf ("%d\n", i);
  return 0;
}
