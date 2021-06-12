#include <stdio.h>

void 
print_simple (int n)
{
  if (n == 1)
    return;
  
  int i = 2;

  while (n % i != 0)
    i++;

  printf("%d ", i);
  print_simple (n / i);
}

int
main (void)
{
  int n;
  scanf ("%d", &n);

  print_simple (n);
  return 0;
}
