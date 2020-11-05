#include "all_func.h"

int
main (int argc, char *argv[])
{
  char *file_name;
  int size, ret;
  double *arr, time, x;

  if (argc < 2 || argc > 3)
    {
      printf ("Usage: %s SIZE (FILENAME)\n", argv[0]);
      return -4;
    }

  size = atoi (argv[1]);
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

  if (argc == 3)
    {
      file_name = argv[2];
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
    }
  else
    rand_array (arr, size);

  printf ("\nEnter X = ");
  if (scanf ("%lf", &x) != 1)
    {
      printf ("Incorrect value X\n");
      free (arr);
      return -7;
    }

  printf ("\nARRAY:\n");
  print_array (arr, size);

  time = clock ();
  size = remove_less_x (arr, size, x);
  time = (clock () - time) / CLOCKS_PER_SEC;

  printf ("\nARRAY_edited:\n");
  print_array (arr, size);

  printf ("\nAnswer: %d\n", size);
  printf ("Time = %.4lf\n", time);

  free (arr);
  return 0;
}

