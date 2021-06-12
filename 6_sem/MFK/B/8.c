#include <stdio.h>

int
main (void)
{
  int n, fl = 0;
  scanf ("%d", &n);
  
  for (; n != 0; n /= 10)
  {
    if (n % 10 == 9)
      fl++;
  }
          
  if (fl == 1)
    printf ("YES\n");
  else
    printf ("NO\n");

  return 0;
}
