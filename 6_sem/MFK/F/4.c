#include <stdio.h>



int
main (void)
{
  int  ans[10], i;
  char c;

  for (i = 0; i < 10; i++)
    ans[i] = 0;

  while(1)
  	{
      scanf ("%c", &c);

      if (c == '.')
        break;
      
      if (c >= '0' && c <= '9')
        ans[c- '0']++;
    }

  for (i = 0; i < 10; i++)
   	if (ans[i] != 0)
  		printf("%d %d\n", i, ans [i]);
  
   
  return 0;
}
