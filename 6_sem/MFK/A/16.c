#include <stdio.h>

int
main (void)
{
  int i, a, b;
  scanf ("%d", &a);

  for (i = 1; i < 3; i++)
  {
  	scanf ("%d", &b);
  	if (!(b > a))
    {
  	  printf("NO\n");
      return 0;
    }
  }

  printf("YES\n");
  return 0;
}
