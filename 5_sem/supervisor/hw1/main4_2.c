#include "all_func.h"

int
main (int argc, char *argv[])
{
  char *file_name;
  int size, ret, k, i, ans;
  //double time;
  char **arr, *str;

  if (argc != 5)
    {
      printf ("Usage: %s SIZE K STR FILENAME\n", argv[0]);
      return -4;
    }

  size = atoi (argv[1]);
  k = atoi (argv[2]);
  str = argv[3];
  file_name = argv[4];

  if (size <= 0 || k < 0)
    {
      printf ("Incorrect values SIZE or K\n");
      return -5;
    }

  arr = (char **) malloc (size * sizeof (char*));
  if (!arr)
    {
      printf ("Not enough memory for array\n");
      return -6;
    }

    ret = read_str_array (file_name, arr, size);
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
  print_str_array (arr, size);

  ans = problem_4_2 (arr, size, k, str);
  printf ("\nAnswer: %d\n", ans);

  printf ("\nARRAY_edited:\n");
  print_str_array (arr, ans);

  for (i = 0; i < size; i++)
    free (arr[i]);
  free(arr);
  return 0;
}
