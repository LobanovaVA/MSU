#include <stdio.h>

#define N 10

void swap_min_max(int size, int a[]);

void swap_min_max(int size, int a[])
{
	int max = a[0], min = a[0], ind_max = 0, ind_min = 0;

	for (int i = 0; i < size; i++)
	{
		if (a[i] < min)
		{
			min = a[i];
			ind_min = i;
		}
		if (a[i] > max)
		{
			max = a[i];
			ind_max = i;
		}
	}

	a[ind_max] = min;
	a[ind_min] = max;
}


int
main (void)
{
	int arr[N];

  	for (int i = 0; i < N; i++)
    	scanf ("%d", arr + i);

  	swap_min_max (N, arr);

	for (int i = 0; i < N; i++)
    	printf ("%d ", arr[i]);
  	
  return 0;
}

