#include <stdio.h>

int
main (void)
{
  int n, i, j, reminder, tmp;
  scanf ("%d", &n);
      
  if (n == 0) 
    return printf ("0\n"), 0;

  for (reminder = n % 10; n > 0; n /= 10, reminder = n % 10)
    printf ("%d", reminder);
          
  printf ("\n");
  return 0;
}
