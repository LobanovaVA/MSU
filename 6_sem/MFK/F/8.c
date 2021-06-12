#include <stdio.h>

#define N 1000

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
	for (int i = 0; i < size - 1; i++)
		if (a[i + 1] - a[i] != 1)
			return a[i] + 1;


	if (a[0] > 1)
		return a[0] - 1;
	else return a[size - 1] + 1;

	return 0;
}



int
main (void)
{
	int a[N], size;

	for (int i = 0; i < N; i++)
  	{
      scanf ("%d", a + i);
      if (a[i] == 0)
      {
      	size = i;
      	break;
      }
    }

  	sort_array (size, a);
  	printf("%d\n", check_array (size, a));

  return 0;
}
