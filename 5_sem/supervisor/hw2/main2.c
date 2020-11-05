#include "addition.h"

int
main (int argc, char **argv){
  const char *file_nmae_A, *file_nmae_B, *str_s;
  int ret;
  if (argc != 4)
    {
      printf ("Usage: %s FILE_NAME_A FILE_NAME_B strS\n", argv[0]);
      return -4;
    }

  file_nmae_A = argv[1];
  file_nmae_B = argv[2];
  str_s = argv[3];

  ret = problem_2 (file_nmae_A, file_nmae_B, str_s);
  if (ret < SUCCESS)
    {
      switch (ret)
        {
        case ERROR_CANNOT_OPEN_INPUT_FILE_A:
          printf ("Cannot open %s\n", file_nmae_A);
          break;
        case ERROR_CANNOT_OPEN_INPUT_FILE_B:
          printf ("Cannot open %s\n", file_nmae_B);
          break;
        case ERROR_CANNOT_READ_INPUT_FILE:
          printf ("Cannot read %s\n", file_nmae_A);
          break;
        case ERROR_CANNOT_WRITE_IN_FILE:
          printf ("Cannot write %s\n", file_nmae_B);
          break;
        case EMPTY_STR_S:
          printf ("Empty string S\n");
          break;
        case ERROR_STR_S:
          printf ("Incorrect string S\n");
          break;
        default:
          printf ("Uknown error %d in either %s or %s\n",
                  ret, file_nmae_A, file_nmae_B);
        }
      return 1;
    }

  printf ("Result = %d\n", ret);
  return 0;
}

