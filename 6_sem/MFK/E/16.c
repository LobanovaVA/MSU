#include <stdio.h>
#define N 10

int
main (void)
{
  int arr[N], i, k, z, count, max = 0, tmp, ans;

  for (i = 0; i < N; i++)
    scanf ("%d", arr + i);

  for (i = 0; i < N; i++)
    {
      tmp = arr[i];
      count = 0;

      for (k = 0; k < N; k++)
        if (tmp == arr[k])
          count++;

      if (count > max)
        {
          max = count;
          ans = tmp;
        }
    }

  printf ("%d\n", ans);  
  return 0;
}
