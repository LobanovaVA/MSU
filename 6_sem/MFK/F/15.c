#include <stdio.h>

#define N 10

int find_num (int size, int a[]);
int find_max_array (int size, int a[]);

int 
find_max_array (int size, int a[])
{
	int max = a[0];
	for (int i = 1; i < size; i++)
		if (a[i] > max)
			max = a[i];

	return max;
}

int find_num (int size, int a[])
{
	int max = find_max_array (size, a);
	int elem, count = 0;
	max = (max < 0) ? -max : max;

	for (int i = 0; i < size; i++)
	{
		elem = a[i];
		elem = (elem < 0) ? -elem : elem;
		if (elem > max)
			count++;
	}

	return count;
}


int
main (void)
{
	int arr[N];

  	for (int i = 0; i < N; i++)
    	scanf ("%d", arr + i);

  	printf ("%d\n", find_num (N, arr));

  	return 0;
}

