#include <stdio.h>

int
main (void)
{
  int n, i;
  scanf ("%d", &n);
  
  for (i = 0; n != 0; i++)
    n /= 10; 
          
  if (i == 3)
    printf ("YES\n");
  else
    printf ("NO\n");

  return 0;
}
