#include <stdio.h>

int
main (void)
{
  int arr[5], i, sum = 0;

  for (i = 0; i < 5; i++)
    scanf ("%d", arr + i);

  for (i = 0; i < 5; i++)
    sum += arr[i];

  printf("%.3f\n", sum / 5.);

  return 0;
}
