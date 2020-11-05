#include "all_func.h"

int
main (int argc, char *argv[])
{
  char *file_name;
  int ans;
  double d;

  if (argc != 2)
    {
      printf ("Usage: %s FILENAME\n", argv[0]);
      return -1;
    }
  file_name = argv[1];

  ans = problem_1_3 (file_name, &d);
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
      return 1;
    }

  printf ("\nAnswer: %d\n", ans);
  if (ans != 0)
    printf ("Standard deviation squared: %.10lf\n", d);
  return 0;
}

