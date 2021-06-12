#include <stdio.h>
#define N 10

int
main (void)
{
  int arr[N], i, k, fl, tmp;

  for (i = 0; i < N; i++)
    scanf ("%d", arr + i);

  for (i = 0; i < N; i++)
    {
      tmp = arr[i];
      fl = 1;

      for (k = 0; k < i; k++)
      	if (tmp == arr[k])
      	  fl = 0;

      for (k = i + 1; k < N; k++)
        if (tmp == arr[k])
          fl = 0;

      if (fl)
        printf ("%d ", tmp);
    }
        
  return 0;
}
