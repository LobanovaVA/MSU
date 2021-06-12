#include <stdio.h>

#define N 30

void find_min_sum (int size, int a[]);

void find_min_sum (int size, int a[])
{
	int i1 = 0, i2 = 1;
	int sum = a[0] + a[1]; 

	for (int i = 0; i < size; i++)
		for (int j = i + 1; j < size; j++)
		{
			if (a[i] + a[j] < sum)
			{
				i1= i;
				i2= j;
				sum = a[i] + a[j];
			}
		}

	printf ("%d %d", i1, i2);
}


int
main (void)
{
	int arr[N];

  	for (int i = 0; i < N; i++)
    	scanf ("%d", arr + i);

  	find_min_sum (N, arr);
  	return 0;
}

