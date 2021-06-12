#include <stdio.h>

#define N 1000

void array_digit (int size, int arr[], int ans[]);

void 
array_digit (int size, int arr[], int ans[])
{
	for (int i = 0; i < size; i++)
		ans[arr[i]]++;
}

int
main (void)
{
  int arr[N], ans[10], i, size = 0;
  char c;

  for (i = 0; i < 10; i++)
    ans[i] = 0;

  for (i = 0; i < N; i++)
  	{
      scanf ("%c", &c);
      if (c == '\n')
      {
        size = i;
        break;
      }
      else
        arr[i] = c - '0';

    }

  array_digit (size, arr, ans);

  for (i = 0; i < 10; i++)
   	if (ans[i] != 0)
  		printf("%d %d\n", i, ans [i]);
  
   
  return 0;
}
