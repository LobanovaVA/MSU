#include <stdio.h>

int
main (void)
{
  int n, sum = 0;
  scanf ("%d", &n);
    
  while (n != 0 && sum < 11)
  {
    sum += n % 10;
    n /= 10;
  }
    
  if (sum == 10)
    printf ("YES\n");
  else
    printf ("NO\n");

  return 0;
}
