#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define N 5

int find_track (int size, int a[][N]);


int find_track (int size, int a[][N])
{
	int track = 0;
	for (int i = 0; i < size; i++)
		track += a[i][i];

	return track;
}


int
main (void)
{
	int arr[N][N];

  	for (int i = 0; i < N; i++)
  		for (int j = 0; j < N; j++)
  		   	scanf ("%d", &(arr[i][j]));

  	printf ("%d\n", find_track (N, arr));

  	return 0;
}

