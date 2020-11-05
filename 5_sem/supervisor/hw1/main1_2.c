#include "all_func.h"

int
main (int argc, char *argv[])
{
  char *file_name_A, *file_name_B;
  int ans;

  if (argc != 3)
    {
      printf ("Usage: %s FILENAME_A FILENAME_B\n", argv[0]);
      return -1;
    }
  file_name_A = argv[1];
  file_name_B = argv[2];

  ans = problem_1_2 (file_name_A, file_name_B);
  if (ans < 0)
    {
      switch (ans)
        {
        case ERROR_CANNOT_OPEN_INPUT_FILE_A:
          printf ("Cannot open %s\n", file_name_A);
          break;
        case ERROR_CANNOT_OPEN_INPUT_FILE_B:
          printf ("Cannot open %s\n", file_name_B);
          break;
        case ERROR_CANNOT_READ_INPUT_FILE_A:
          printf ("Cannot read %s\n", file_name_A);
          break;
        case ERROR_CANNOT_READ_INPUT_FILE_B:
          printf ("Cannot read %s\n", file_name_B);
          break;
        case ERROR_EMPTY_INPUT_FILE_A:
          printf ("Empty file %s\n", file_name_A);
          break;
        case ERROR_EMPTY_INPUT_FILE_B:
          printf ("Empty file %s\n", file_name_B);
          break;
        case ERROR_EMPTY_INPUT_FILE:
          printf ("Empty files %s and %s\n", file_name_A, file_name_B);
          break;
        default:
          printf ("Unknown error %d in %s or %s\n", ans, file_name_A, file_name_B);
        }
      return 1;
    }

  printf ("\nAnswer: %d\n", ans);
  return 0;

}
