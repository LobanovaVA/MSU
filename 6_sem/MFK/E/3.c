#include <stdio.h>

int
main (void)
{
  int arr[10], i;
  int min, max, i_max = 0, i_min = 0;

  for (i = 0; i < 10; i++)
    scanf ("%d", arr + i);

  min = arr[0];
  max = arr[0];
  for (i = 1; i < 10; i++)
  {
    if (arr[i] < min)
      {
        min = arr[i];
        i_min = i;
      }

    if (arr[i] > max)
      {
        max = arr[i];
        i_max = i;
      }
  }

  printf("%d %d %d %d\n", i_max + 1, max, i_min + 1, min);

  return 0;
}
