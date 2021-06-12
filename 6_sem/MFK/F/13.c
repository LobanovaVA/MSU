#include <stdio.h>

#define N 10

int find_num (int size, int arr[], int a, int b);

int find_num (int size, int arr[], int a, int b)
{
	int count = 0;

	for (int i = 0; i < size; i++)
		if (arr[i] >= a && arr[i] <= b)
			count++;

	return count;
}


int
main (void)
{
	int arr[N];
	int a, b;
	scanf ("%d %d", &a, &b);

  	for (int i = 0; i < N; i++)
    	scanf ("%d", arr + i);

  	printf ("%d\n", find_num (N, arr, a, b));
  	return 0;
}

