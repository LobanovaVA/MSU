#include <stdio.h>

int
main (void)
{
  int arr[12], i, sum = 0;

  for (i = 0; i < 12; i++)
    scanf ("%d", arr + i);

  for (i = 0; i < 12; i++)
    sum += arr[i];

  printf("%.2f\n", sum / 12.);

  return 0;
}
