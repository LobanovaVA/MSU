#include <stdio.h>
#include <stdlib.h>

#define N 5

int find_track (int size, int a[][N]);
int find_num (int size, int a[][N], double d);


int find_track (int size, int a[][N])
{
	int track = 0;
	for (int i = 0; i < size; i++)
		track += a[i][i];

	return track;
}



int find_num (int size, int a[][N], double d)
{
	int count = 0;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (a[i][j] > d)
				count++;
	

	return count;
}



int
main (void)
{
	int arr[N][N];

  	for (int i = 0; i < N; i++)
  		for (int j = 0; j < N; j++)
  		   	scanf ("%d", &(arr[i][j]));

  	printf ("%d\n", find_num (N, arr, ((double) find_track (N, arr)) / N));

  	return 0;
}

