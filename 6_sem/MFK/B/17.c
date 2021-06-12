#include <stdio.h>

int
main (void)
{
  int i = 2, elem3 = 3, fl = 1;
  double sum = 1., elem = 1.;
  
  while (elem > 0.001)
    {
      elem = (double) i / ((i + 1) * elem3);

      i += 2;
      elem3 *= 3;

      if (fl)
        {
          sum += elem;
          fl = 0;
        }
      else 
      {
        sum -= elem;
        fl = 1;
      }
    }
    
  printf ("%.3f\n", sum);
  return 0;
}
