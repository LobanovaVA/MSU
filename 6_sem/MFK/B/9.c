#include <stdio.h>

int
main (void)
{
  int n, fl = 0;
  scanf ("%d", &n);
  
  for (; n != 0; n /= 10)
  {
    if ((n % 10) % 2 != 0)
      {
        printf ("NO\n");
        return 0;
      }
  }
          
  printf ("YES\n");
  return 0;
}
