#include "all_func.h"

int
main (int argc, char *argv[])
{
  double eps, x, a, b;
  double *arr;
  int ret, m, mode;

  /* === get args === */
  if (! (argc == 6 && sscanf (argv[1], "%d", &m) == 1
         && sscanf (argv[2], "%lf", &a) == 1
         && sscanf (argv[3], "%lf", &b) == 1
         && sscanf (argv[4], "%lf", &eps) == 1
         && sscanf (argv[5], "%d", &mode) == 1
         && mode > 0 && mode < 6 && m > 0) )
    {
      printf ("ERROR: Usage: %s M A B eps mode\n", argv[0]);
      return ERROR_USAGE_ARGC;
    }


  /* === solve === */
  if (mode == 4 && a < 0)
    {
      printf("\nWARNING: cannot apply formula 4\n");
      return ERROR_SOLVE;
    }

  arr = (double *) malloc (3 * (m + 1) * sizeof (double));
  if (!arr)
    {
      printf ("ERROR: Can not allocate memory for array\n");
      return ERROR_ALLOCATE_MEMORY;
    }

  ret = problem_2_6 (m, arr, a, b, eps, &x, mode);
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
      free (arr);
      return ERROR_SOLVE;
    }

  printf ("\nAnswer: %f\n", x);
  printf ("\nf (x) = %f\n", f (x, mode));
  printf ("Solve iteration = %d\n", ret);
  free (arr);
  return 0;
}
