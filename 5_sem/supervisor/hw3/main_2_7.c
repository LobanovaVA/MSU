#include "all_func.h"

int
main (int argc, char *argv[])
{
  double x0, eps, x;
  int ret, mode;

  /* === get args === */
  if (! (argc == 4 && sscanf (argv[1], "%lf", &x0) == 1
         && sscanf (argv[2], "%lf", &eps) == 1
         && sscanf (argv[3], "%d", &mode) == 1
         && mode > 0 && mode < 6) )
    {
      printf ("ERROR: Usage: %s x0 eps mode\n", argv[0]);
      return ERROR_USAGE_ARGC;
    }

  /* === solve === */
  if (mode == 4 && x0 < 0)
    {
      printf("\nWARNING: cannot apply formula 4\n");
      return ERROR_SOLVE;
    }

  ret = problem_2_7 (x0, eps, &x, mode);

  if (ret < SUCCESS)
    {
      switch(ret){
        case ERROR_NO_SOLUTION:
          printf("ERROR: Root is not found\n");
          break;
        case ERROR_MAX_ITERATION:
          printf("ERROR: Iteration limit exceeded (%d)\n", MAX_IT);
          break;
        default: printf("ERROR: Uknown error %d", ret);
        }
      return ERROR_SOLVE;
    }

  printf ("\nAnswer: %f\n", x);
  printf ("\nf (x) = %f\n", f (x, mode) - x);
  printf ("Solve iteration = %d\n", ret);
  return 0;
}
