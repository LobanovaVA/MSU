#include <stdio.h>

#define N 20

void sort_array_chet (int size, int a[]);

void 
sort_array_chet (int size, int a[])
{
	int tmp, count = 0;
	for (int i = 0; i < size - count; i++)
	{
		if (a[i] % 2 != 0)
		{
			count++;
			tmp = a[i];

			for (int j = i; j < size - 1; j++)
				a[j] = a[j + 1];

			a[size - 1] = tmp;
			i--;
		}
	}
}



int
main (void)
{
  int arr[N], i;

  for (i = 0; i < N; i++)
    scanf ("%d", arr + i);

  sort_array_chet (N, arr);

  for (i = 0; i < N; i++)
    printf("%d ", arr [i]);


  return 0;
}
