#include <stdio.h>

int check (int n);

int 
check (int n)
{
  int count = 0;

  if (n == 0)
    return 0;

  for (int i = 0; i <= n; i += 8)
    if ((n - i) % 6 == 0)
      count++;

  return count;
}
int
main (void)
{
  int n;
  scanf ("%d", &n);

  printf ("%d\n", check (n));

  return 0;
}