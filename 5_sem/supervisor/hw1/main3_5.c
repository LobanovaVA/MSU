#include "all_func.h"

int
main (int argc, char *argv[])
{
  char *file_name;
  int size, ret;
  double *arr_1, *arr_2, time;

  if (argc != 3)
    {
      printf ("Usage: %s SIZE FILENAME\n", argv[0]);
      return -4;
    }

  size = atoi (argv[1]);
  file_name = argv[2];

  if (size <= 0)
    {
      printf ("Incorrect values SIZE\n");
      return -5;
    }

  arr_1 = (double *) malloc (size * sizeof (double));
  if (!arr_1)
    {
      printf ("Not enough memory for array_1\n");
      return -6;
    }

  arr_2 = (double *) malloc (size * sizeof (double));
  if (!arr_2)
    {
      printf ("Not enough memory for array_2\n");
      free (arr_1);
      return -6;
    }

  ret = read_array (file_name, arr_1, size);
  if (ret < 0)
    {
      switch (ret)
        {
        case ERROR_CANNOT_OPEN_INPUT_FILE:
          printf ("Cannot open %s\n", file_name);
          break;
        case ERROR_CANNOT_READ_INPUT_FILE:
          printf ("Cannot read %s\n", file_name);
          break;
        default:
          printf ("Unknown error %d in %s\n", ret, file_name);
        }
      free (arr_1);
      free (arr_2);
      return 1;
    }

  printf ("\nARRAY:\n");
  print_array (arr_1, size);

  time = clock ();
  merge_sort (arr_1, arr_2, size);
  time = (clock () - time) / CLOCKS_PER_SEC;

  printf ("\nARRAY_sort:\n");
  print_array (arr_1, size);

  printf ("\nTime = %.4lf\n", time);
  check_sort (arr_1, size);

  free (arr_1);
  free (arr_2);
  return 0;
}
