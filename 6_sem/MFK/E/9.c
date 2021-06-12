#include <stdio.h>
#define N 10

int
main (void)
{
  int arr[N], i, tmp;

  for (i = 0; i < N; i++)
    scanf ("%d", arr + i);

  tmp = arr[N -1];
  for (i = N - 1; i > 0; i--)
    arr[i] = arr[i - 1];
  arr[0] =tmp;
    
  for (i = 0; i < N; i++)
    printf ("%d ", arr[i]);

  return 0;
}
