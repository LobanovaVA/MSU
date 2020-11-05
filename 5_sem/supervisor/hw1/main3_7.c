#include "all_func.h"

int
main (int argc, char *argv[])
{
  char *file_name;
  int size, ret;
  double *arr, time;

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

  arr = (double *) malloc (size * sizeof (double));
  if (!arr)
    {
      printf ("Not enough memory for array\n");
      return -6;
    }

  ret = read_array (file_name, arr, size);
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
      free (arr);
      return 1;
    }

  printf ("\nARRAY:\n");
  print_array (arr, size);

  time = clock ();
  heap_sort (arr, size);
  time = (clock () - time) / CLOCKS_PER_SEC;

  printf ("\nARRAY_sort:\n");
  print_array (arr, size);

  printf ("\nTime = %.4lf\n", time);
  check_sort (arr, size);

  free (arr);
  return 0;
}
