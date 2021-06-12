#include <stdio.h>

int
main (void)
{
  int i = 2, elem3 = 3, fl = 1;
  int fib1 = 1, fib2 = 1, fib;
  double sum = 1., elem = 1.;
  
  while (elem > 0.001)
    {
      fib = fib1 + fib2;
      elem = (double) i / (fib * elem3);

      i += 2;
      elem3 *= 3;
      fib1 = fib2;
      fib2 = fib; 

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
