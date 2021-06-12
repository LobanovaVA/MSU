#include <stdio.h>

#define N 100

int check_array (int size, int a[]);
void sort_array (int size, int a[]);

void 
sort_array (int size, int a[])
{
	int tmp;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size - i - 1; j++)
			if (a[j] > a[j + 1])
			{
				tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
			}
}


int
check_array (int size, int a[])
{
	for (int i = 1; i < size; i++)
		if (a[i - 1] == a[i])
			return 1;

	return 0;
}



int
main (void)
{
	int arr[N];

  	for (int i = 0; i < N; i++)
    	scanf ("%d", arr + i);

  	sort_array (N, arr);

  	if (check_array (N, arr))
    	printf("YES\n");
	else
	printf("NO\n"); 

  return 0;
}
