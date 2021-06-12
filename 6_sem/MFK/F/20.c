#include <stdio.h>

#define N 10

int chet_prod (int n);
int nechet_prod (int n);
void f (int size, int arr[]);


int 
chet_prod (int n)
{
	int p = 1, d;

	if (n == 0) 
		return 0;

	while (n != 0)
	{
		d = n % 10;

		if (d % 2 == 0)
			p *= d;

		n /= 10;
	}

	return p;
}


int 
nechet_prod (int n)
{
	int p = 1, d;

	if (n == 0) 
		return 0;

	while (n != 0)
	{
		d = n % 10;

		if (d % 2 != 0)
			p *= d;

		n /= 10;
	}
	
	return p;
}


void 
f (int size, int arr[])
{
	int c_chet = 0;

	for (int i = 0; i < size; i++)
		if (arr[i] % 2 == 0)
			c_chet++;

	if (c_chet > size - c_chet)
	{
		for (int i = 0; i < size; i++)
			if (arr[i] % 2 != 0)
				arr[i] = nechet_prod (arr[i]);
	}
	else
	{
		for (int i = 0; i < size; i++)
			if (arr[i] % 2 == 0)
				arr[i] = chet_prod (arr[i]);
	}
}

int
main (void)
{
	int arr[N];

  	for (int i = 0; i < N; i++)
    	scanf ("%d", arr + i);

    f (N, arr);

    for (int i = 0; i < N; i++)
    {
    	printf ("%d ", arr[i]);
    }

  	return 0;
}

