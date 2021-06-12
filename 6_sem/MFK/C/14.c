#include <stdio.h>

int 
my_check_num_sum (int n)
{
  int i, sum = 0;
  while (n != 0)
    {
       sum += n % 10;
       n /= 10;
    }

  if (sum % 2 == 0)
  	return 1;
  else 
  	return 0;
}

int
main (void)
{
  int n;
  scanf ("%d", &n);

  if (my_check_num_sum (n))
  	printf("YES\n");
  else 
  	printf("NO\n");

  return 0;
}
