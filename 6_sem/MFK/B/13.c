#include <stdio.h>

int
main (void)
{
  int n, chet = 0, nechet = 0;
  scanf ("%d", &n);
  
  if (n == 0)
    return printf ("1 0\n"), 0;
    
  for (; n != 0; n /= 10)
  {
    if ((n % 10) % 2 == 0)
      chet++;
    else nechet++;
  }
          
  printf ("%d %d\n", chet, nechet);
  return 0;
}
