#include <stdio.h>

#define N 100

int
main (void)
{
	int a[N], j;

  	for (int i = 0; i < N; i++)
    	scanf ("%d", a + i);

    printf("[");

    if (a[0] != 0)
    	printf("0,");

    for (int i = 0; i < N; )
    {
    	for (j = i + 1; j < N; j++)
    		if (a[i] != a[j])
    				break;
    			
    	printf("%d", j - i);
    	i = j;
    	
    	if (i < N)
    		printf(",");
    }

	printf("]\n");

  return 0;
}
