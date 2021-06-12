#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define N 10

int find_sum_of_strmax (int size, int a[][N]);


int find_sum_of_strmax (int size, int a[][N])
{
	int sum = 0, max;
	for (int i = 0; i < size; i++)
	{
		max = a[i][0];
		for (int j = 0; j < size; j++)
			if (a[i][j] > max)
				max = a[i][j];

		sum += max;
	}

	return sum;
}


int
main (void)
{
	int arr[N][N];

  	for (int i = 0; i < N; i++)
  		for (int j = 0; j < N; j++)
  		   	scanf ("%d", &(arr[i][j]));

  	printf ("%d\n", find_sum_of_strmax (N, arr));

  	return 0;
}

