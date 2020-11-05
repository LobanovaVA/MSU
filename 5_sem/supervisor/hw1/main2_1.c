#include "all_func.h"

int
main (int argc, char *argv[])
{
  char *file_name, *file_name_arr;
  int size, ret, ans;
  double *arr, time;

  if (argc < 3 || argc > 4)
    {
      printf ("Usage: %s SIZE FILENAME (FILENAME_AR) \n", argv[0]);
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

  if (argc == 4)
    {
      file_name_arr = argv[3];
      ret = read_array (file_name_arr, arr, size);
      if (ret < 0)
        {
          switch (ret)
            {
            case ERROR_CANNOT_OPEN_INPUT_FILE:
              printf ("Cannot open %s\n", file_name_arr);
              break;
            case ERROR_CANNOT_READ_INPUT_FILE:
              printf ("Cannot read %s\n", file_name_arr);
              break;
            default:
              printf ("Unknown error %d in %s\n", ret, file_name_arr);
            }
          free (arr);
          return 1;
        }
    }
  else
    rand_array (arr, size);

  printf ("\nARRAY:\n");
  print_array (arr, size);

  time = clock ();
  ans = search_subserie (file_name, arr, size);
  if (ans < 0)
    {
      switch (ans)
        {
        case ERROR_CANNOT_OPEN_INPUT_FILE:
          printf ("Cannot open %s\n", file_name);
          break;
        case ERROR_CANNOT_READ_INPUT_FILE:
          printf ("Cannot read %s\n", file_name);
          break;
        case ERROR_EMPTY_INPUT_FILE:
          printf ("Empty file %s\n", file_name);
          break;
        default:
          printf ("Unknown error %d in %s\n", ans, file_name);
        }
      free (arr);
      return 1;
    }

  time = (clock () - time) / CLOCKS_PER_SEC;
  printf ("\nAnswer: %d\n", ans);
  printf ("Time = %.4lf\n", time);
  free (arr);
  return 0;
}

