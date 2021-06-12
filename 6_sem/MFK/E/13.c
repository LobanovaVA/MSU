#include <stdio.h>
#define N 10

int
main (void)
{
  int arr[N], i, k, c, tmp;;

  for (i = 0; i < N; i++)
    scanf ("%d", arr + i);

  for (i = 0; i < N; i++)
    {
      if ((arr[i] / 10) % 10 == 0)
        printf("%d ", arr[i]);
    }
    
  return 0;
}
