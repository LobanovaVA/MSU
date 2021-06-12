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
      c = i;
      for (k = i; k < N; k++)
        {
          if (arr[k] % 10 < arr[c] % 10)
            c = k;
            
        }
      tmp = arr[i];
      arr[i] = arr[c];
      arr[c] = tmp;
    }
    
  for (i = 0; i < N; i++)
    printf ("%d ", arr[i]);

  return 0;
}
