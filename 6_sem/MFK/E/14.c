#include <stdio.h>
#define N 10

int
main (void)
{
  int arr[N], ans[N / 2], tmp;
  int i, k, z, count = 0;

  for (i = 0; i < N; i++)
    scanf ("%d", arr + i);

  for (i = 0; i < N; i++)
    {
      tmp = arr[i];

      for (k = 0; k < i; k++)
      	if (tmp == arr[k])
      	  {
      	  	for (z = 0; z < count; z++)
      	  	 if (tmp == ans[z])
      	  	   break;

      	  	if (z == count)
      	  	  {
      	  	  	ans[count] = tmp;
      	  	    count++;
      	  	  }

      	  	break;
      	  }
    }

  for (i = 0; i < count; i++)
    printf ("%d ", ans[i]);

  printf("\n");    
  return 0;
}
