#include "all_func.h"

int
main (int argc, char *argv[])
{
  double a, eps, r;
  int ret, mode;

  /* === get args === */
  if (! (argc == 4 && sscanf (argv[1], "%lf", &a) == 1
         && sscanf (argv[2], "%lf", &eps) == 1
         && sscanf (argv[3], "%d", &mode) == 1
         && mode > 0 && mode < 6 && eps > 0) )
    {
      printf ("ERROR: Usage: %s A eps mode\n", argv[0]);
      return ERROR_USAGE_ARGC;
    }

  /* === solve === */
  if (mode == 4 && a < 0)
    {
      printf("\nWARNING: cannot apply formula 4\n");
      return ERROR_SOLVE;
    }

  ret = problem_3_8 (a, eps, &r, mode);

  if (ret < SUCCESS)
    {
      switch(ret){
        case ERROR_NO_SOLUTION:
          printf("ERROR: Integral is not found\n");
          break;
        case ERROR_MAX_STEP:
          printf("ERROR: Step limit exceeded\n");
          break;
        case ERROR_MAX_ITERATION:
          printf("ERROR: Iteration limit exceeded (%d)\n", MAX_IT);
          break;
        default: printf("ERROR: Uknown error %d", ret);
        }
      return ERROR_SOLVE;
    }

  printf ("\nIntegral = %f\n", r);
  printf ("Solve iteration = %d\n", ret);
  return 0;
}
