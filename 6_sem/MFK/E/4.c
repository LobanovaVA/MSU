#include <stdio.h>

int
main (void)
{
  int arr[10], i;
  int max_1, max_2;

  for (i = 0; i < 10; i++)
    scanf ("%d", arr + i);

  if (arr[0] > arr[1])
    {
      max_1 = arr[0];
      max_2 = arr[1];
    }
  else
    {
      max_1 = arr[1];
      max_2 = arr[0];
    }

  for (i = 2; i < 10; i++)
  {
    if (arr[i] >= max_1)
      {
        max_2 = max_1;
        max_1 = arr[i];
      }
    else
      {
        if (arr[i] > max_2)
          max_2 = arr[i];
      }
  }

  printf("%d\n", max_2 + max_1);
  return 0;
}
