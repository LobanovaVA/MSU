#include <stdio.h>
#define LEN 1234
int
main (void)
{
  int arr[LEN], n, i, N, c, k, tmp;

  scanf ("%d", &n);
  if (n == 0)
    printf ("0"); 

  for(i = 0; n > 0; i++, n /= 10)
    arr[i] = n % 10;
  N = i;

  for (i = 0; i < N; i++)
    {
      c = i;
      for (k = i; k < N; k++)
        {
          if (arr[k] > arr[c])
            c = k; 
        }
        
      tmp = arr[i];
      arr[i] = arr[c];
      arr[c] = tmp;
    }

  for (i = 0; i < N; i++)
    printf ("%d", arr[i]);

  return 0;
}
