#include "all_func.h"

int
main (int argc, char *argv[])
{
  double a, b, ans;
  int n, mode;

  /* === get args === */
  if (! (argc == 5 && sscanf (argv[1], "%lf", &a) == 1
         && sscanf (argv[2], "%lf", &b) == 1
         && sscanf (argv[3], "%d", &n) == 1
         && sscanf (argv[4], "%d", &mode) == 1
         && mode > 0 && mode < 6 && n > 0) )
    {
      printf ("ERROR: Usage: %s A B n > 0 mode\n", argv[0]);
      return ERROR_USAGE_ARGC;
    }

  /* === solve === */
  if (mode == 4 && a < 0)
    {
      printf("\nWARNING: cannot apply formula 4\n");
      return ERROR_SOLVE;
    }

  ans = problem_3_1 (a, b, n, mode);
  printf("\nIntegral = %f\n", ans);

  return 0;
}
