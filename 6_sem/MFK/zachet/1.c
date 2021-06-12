#include <stdio.h>

#define N 30

int check (int size, int arr[]);

int 
check (int size, int arr[])
{

  for (int i = 1; i < size; i++)
    if (!(arr[i] < arr[i - 1]))
      return 0;

  return 1;
}

int
main (void)
{
  int arr[N];

  for (int i = 0; i < N; i++)
    scanf ("%d", arr + i);

  if (check (N, arr))
    printf ("YES\n");
  else
    printf ("NO\n");

  return 0;
}
