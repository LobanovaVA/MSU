#include "all_func.h"

int
main (int argc, char *argv[])
{
  char *file_name;
  int k, ans;

  if (argc != 3)
    {
      printf ("Usage: %s K FILENAME\n", argv[0]);
      return -4;
    }
  k = atoi (argv[1]);
  if (k <= 0)
    {
      printf ("Incorrect value k\n");
      return -5;
    }
  file_name = argv[2];

  ans = problem_1_1 (file_name, k);
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
        default:
          printf ("Unknown error %d in %s\n", ans, file_name);
        }
      return 1;
    }

  printf ("\nAnswer: %d\n", ans);
  return 0;

}

