#include <stdio.h>

void 
print_simple (int n)
{
  int i = 2;
  while (n > 1)
  {
  	if (n % i == 0)
  	{
  	  printf ("%d ", i);
  	  n /= i;
  	}
  	else 
  	  i++;
  }
}

int
main (void)
{
  int n;
  scanf ("%d", &n);

  print_simple(n);
  return 0;
}
