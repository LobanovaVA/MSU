#include "all_func.h"

int
main (int argc, char *argv[])
{
  char *filename_X, *filename_Y;
  double *arr_X, *arr_Y;
  double x0, ans;
  int size, ret;

  /* === get args === */
  if (! (argc == 5 && sscanf (argv[2], "%lf", &x0) == 1
         && sscanf (argv[1], "%d", &size) == 1 && size > 0) )
    {
      printf ("ERROR: Usage: %s SIZE x0 FILENAME_X FILENAME_Y\n", argv[0]);
      return ERROR_USAGE_ARGC;
    }

  filename_X = argv[3];
  filename_Y = argv[4];


  /* === memory allocation === */
  arr_X = (double *) malloc (size * sizeof (double));
  if (!arr_X)
    {
      printf ("ERROR: Can not allocate memory for arr_X\n");
      return ERROR_ALLOCATE_MEMORY;
    }

  arr_Y = (double *) malloc (size * sizeof (double));
  if (!arr_Y)
    {
      printf ("ERROR: Can not allocate memory for arr_Y\n");
      free (arr_X);
      return ERROR_ALLOCATE_MEMORY;
    }


  /* === read arrays === */
  ret = read_array (size, arr_X, filename_X);
  if (ret != SUCCESS)
    {
      switch (ret)
        {
        case ERROR_CANNOT_OPEN_INPUT_FILE:
          printf ("ERROR: Cannot open input file %s\n", filename_X);
          break;
        case ERROR_CANNOT_READ_INPUT_FILE:
          printf ("Cannot read %s\n", filename_X);
          break;
        default:
          printf ("Unknown error %d in %s\n", ret, filename_X);
        }
      free (arr_X);
      free (arr_Y);
      return ERROR_INPUT_FILE;
    }

  ret = read_array (size, arr_Y, filename_Y);
  if (ret != SUCCESS)
    {
      switch (ret)
        {
        case ERROR_CANNOT_OPEN_INPUT_FILE:
          printf ("ERROR: Cannot open input file %s\n", filename_Y);
          break;
        case ERROR_CANNOT_READ_INPUT_FILE:
          printf ("Cannot read %s\n", filename_Y);
          break;
        default:
          printf ("Unknown error %d in %s\n", ret, filename_Y);
        }
      free (arr_X);
      free (arr_Y);
      return ERROR_INPUT_FILE;
    }


  /* === solve === */
  ans = problem_1_1 (size, x0, arr_X, arr_Y);
  printf ("\nAnswer: %lf\n", ans);

  free (arr_X);
  free (arr_Y);

  return 0;
}
