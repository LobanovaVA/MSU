#include <stdio.h>
#define N 12

int 
get_ind (int i)
{
  int part = N / 3;
  int mod = i % part;

  if (mod < part / 2)
    return i - mod + part - 1 - mod;
  return i;
}

int
main (void)
{
  int arr[N], i, tmp;

  for (i = 0; i < N; i++)
    scanf ("%d", arr + i);

  for (i = 0; i < N; i++)
    {
      tmp = arr[get_ind (i)];
      arr[get_ind (i)] = arr[i];
      arr[i] = tmp;
    }


  for (i = 0; i < N; i++)
    printf ("%d ", arr[i]);

  return 0;
}
