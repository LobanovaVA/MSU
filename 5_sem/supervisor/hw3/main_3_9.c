#include "all_func.h"

int
main (int argc, char *argv[])
{
  double a, b, eps, r;
  int ret, mode;

  /* === get args === */
  if (! (argc == 5 && sscanf (argv[1], "%lf", &a) == 1
         && sscanf (argv[2], "%lf", &b) == 1
         && sscanf (argv[3], "%lf", &eps) == 1
         && sscanf (argv[4], "%d", &mode) == 1
         && mode > 0 && mode < 7 && eps > 0) )
    {
      printf ("ERROR: Usage: %s A eps mode\n\n", argv[0]);
      printf ("| mode |  x (t)  |          y (t)          |\n");
      printf ("|------|---------|-------------------------|\n");
      printf ("| 1..5 |    t    | f from previos problems |\n");
      printf ("|   6  | cos (t) |         sin (t)         |\n");
      return ERROR_USAGE_ARGC;
    }

  /* === solve === */
  if (mode == 4 && a < 0)
    {
      printf("\nWARNING: cannot apply formula 4\n");
      return ERROR_SOLVE;
    }

  ret = problem_3_9 (a, b, eps, &r, mode);

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

  printf ("\nLenght = %f\n", r);
  printf ("Solve iteration = %d\n", ret);
  return 0;
}
