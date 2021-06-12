#include <stdio.h>

int 
my_nod (int a, int b)
{
  if (a == 0 || b == 0)
  	return a + b;
    
  while (a != b)
    {
      if (a > b) 
      	a -=b;
      else 
      	b -=a;
    }
    
  return a;
}

int
main (void)
{
  int a, b;
  scanf ("%d %d", &a, &b);

  printf ("%d\n", my_nod (a, b));

  return 0;
}
