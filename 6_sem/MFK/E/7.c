#include <stdio.h>
#define N 10

int 
get_ind (int i)
  {
    if (i < N / 4)
	  return N / 2 - i - 1;
	if (i > N / 4 * 3)
	  return N - i - 1 + N / 2; 
	return i;
}

int
main (void)
{
  int arr[N], i, tmp;

  for (i = 0; i < N; i++)
    scanf ("%d", arr + i);

  for (i = 0; i < N; i++)
    {
      tmp = arr[get_ind (i)];
      arr[get_ind (i)] = arr[i];
      arr[i] = tmp;
    }


  for (i = 0; i < N; i++)
    printf ("%d ", arr[i]);

  return 0;
}
