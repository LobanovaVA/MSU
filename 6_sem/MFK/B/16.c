#include <stdio.h>

int
main (void)
{
  int a, b;
  scanf ("%d %d", &a, &b);
  
  if (a == 0 || b == 0)
  	return printf ("%d\n", a + b), 0;
    
  while (a != b)
    {
      if (a > b) 
      	a -=b;
      else 
      	b -=a;
    }
    
  
  printf ("%d\n", a);
  return 0;
}
