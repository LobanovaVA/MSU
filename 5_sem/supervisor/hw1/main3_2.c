#include "all_func.h"

int
main (int argc, char *argv[])
{
  char *file_name_1, *file_name_2;
  int size_1, size_2, ret;
  double *arr_1, *arr_2, *arr_ans;
  double time;

  if (argc != 5)
    {
      printf ("Usage: %s SIZE_1 SIZE_2 FILENAME_1 FILENAME_2\n", argv[0]);
      return -4;
    }
  size_1 = atoi (argv[1]);
  size_2 = atoi (argv[2]);
  file_name_1 = argv[3];
  file_name_2 = argv[4];

  if (size_1 <= 0 || size_2 <= 0)
    {
      printf ("Incorrect values SIZE\n");
      return -5;
    }

  arr_1 = (double *) malloc (size_1 * sizeof (double));
  if (!arr_1)
    {
      printf ("Not enough memory for array_1\n");
      return -6;
    }

  arr_2 = (double *) malloc (size_2 * sizeof (double));
  if (!arr_2)
    {
      printf ("Not enough memory for array_2\n");
      free (arr_1);
      return -6;
    }

  arr_ans = (double *) malloc ((size_1 + size_2) * sizeof (double));
  if (!arr_ans)
    {
      printf ("Not enough memory for array_ans\n");
      free (arr_1);
      free (arr_2);
      return -6;
    }

  ret = read_array (file_name_1, arr_1, size_1);
  if (ret < 0)
    {
      switch (ret)
        {
        case ERROR_CANNOT_OPEN_INPUT_FILE:
          printf ("Cannot open %s\n", file_name_1);
          break;
        case ERROR_CANNOT_READ_INPUT_FILE:
          printf ("Cannot read %s\n", file_name_1);
          break;
        default:
          printf ("Unknown error %d in %s\n", ret, file_name_1);
        }
      free (arr_1);
      free (arr_2);
      free (arr_ans);
      return 1;
    }

  ret = read_array (file_name_2, arr_2, size_2);
  if (ret < 0)
    {
      switch (ret)
        {
        case ERROR_CANNOT_OPEN_INPUT_FILE:
          printf ("Cannot open %s\n", file_name_2);
          break;
        case ERROR_CANNOT_READ_INPUT_FILE:
          printf ("Cannot read %s\n", file_name_2);
          break;
        default:
          printf ("Unknown error %d in %s\n", ret, file_name_2);
        }
      free (arr_1);
      free (arr_2);
      free (arr_ans);
      return 1;
    }

  printf ("\nARRAY_1:\n");
  print_array (arr_1, size_1);
  printf ("\nARRAY_2:\n");
  print_array (arr_2, size_2);

  time = clock ();
  merge (size_1, size_2, arr_1, arr_2, arr_ans);
  time = (clock () - time) / CLOCKS_PER_SEC;

  printf ("\nARRAY_ans:\n");
  print_array (arr_ans, size_1 + size_2);
  printf ("\nTime = %.4lf\n", time);

  free (arr_1);
  free (arr_2);
  free (arr_ans);
  return 0;
}
