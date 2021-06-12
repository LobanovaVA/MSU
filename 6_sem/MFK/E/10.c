#include <stdio.h>
#define N 12

int 
gcd (int a, int b)
{
  while(a != b)
    {
      if(a>b) a = (a % b) ? a % b : b;
      if(b>a) b = (b % a) ? b % a : a;
    }

  return a;
}

void 
right_shift_on_k (int *a, int n, int k)
{
  int s, i, nod = gcd (n,k);
  double a0;
  
  for ( s = nod - 1; s >= 0; s--)
    {
      a0 = a[(s + (n / nod - 1) * k) % n];
      for (i = n / nod - 1; i > 0; i--)
        a[(s + i * k) % n] = a[(s + (i - 1) * k) % n];
      a[s] = a0;
    }
} 

int
main (void)
{
  int arr[N], i, tmp, new_k, k = 0;

  for (i = 0; i < N; i++)
    scanf ("%d", arr + i);

  right_shift_on_k (arr, N, 4);
    
  for (i = 0; i < N; i++)
    printf ("%d ", arr[i]);

  return 0;
}
