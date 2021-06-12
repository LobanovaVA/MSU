#include <stdio.h>

void
f (int i, int n)
{
  if (n < 1)
  	return;

  for (int k = 0; k < i && k < n; k++)
  	printf ("%d ", i);

  return f (i + 1, n - i);
}

int
main (void)
{
  int n;
  scanf ("%d", &n);

  f (1, n);

  return 0;
}
