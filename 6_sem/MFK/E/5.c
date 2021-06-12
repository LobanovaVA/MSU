#include <stdio.h>

int
main (void)
{
  int arr[10], i, sum = 0;

  for (i = 0; i < 10; i++)
    scanf ("%d", arr + i);

  for (i = 0; i < 10; i++)
    if (arr[i] > 0)
      sum += arr[i];


  printf("%d\n", sum);
  return 0;
}
