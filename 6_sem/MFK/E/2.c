#include <stdio.h>

int
main (void)
{
  int arr[5], i, min;

  for (i = 0; i < 5; i++)
    scanf ("%d", arr + i);

  min = arr[0];
  for (i = 1; i < 5; i++)
    if (arr[i] < min)
    	min = arr[i];

  printf("%d\n", min);

  return 0;
}
