#include "addition.h"

size_t
get_IND (size_t i, size_t j, size_t matrix_size)
{
  size_t first_ind, second_ind, pos;
  first_ind  = (i < j) ? i : j;
  second_ind = (i < j) ? j : i;
  pos = first_ind;
  pos = (pos * pos + pos) >> 1;
  pos = first_ind * matrix_size + second_ind - pos;
  return pos;
}

inline bool
is_small (double value, double eps)
{
  return fabs (value) < eps;
}


void
printf_main_process (const char *format, ...)
{
  int my_rank;
  MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);

  va_list args;
  va_start (args, format);

  if (my_rank == MAIN_PROCESS)
    vprintf (format, args);

  va_end (args);
}

int
get_args (const int argc, char **argv, size_arguments &size_args, int &mode)
{
  int matrix_size, block_size, print_size;

  if (! ( (argc == 5 || argc == 6)
          && sscanf (argv[1], "%d", &matrix_size) == 1 && matrix_size > 0
          && sscanf (argv[2], "%d", &block_size) == 1 && block_size > 0
          && sscanf (argv[3], "%d", &print_size) == 1 && print_size >= 0
          && sscanf (argv[4], "%d", &mode) == 1 && mode >= 0 && mode < 5 ))
    {
      printf_main_process ("ERROR: Usage: %s matrix_SIZE block_SIZE print_SIZE MODE (FILENAME)\n", argv[0]);
      return ERR_USAGE_ARGC;
    }

  if (block_size > matrix_size)
    {
      printf_main_process ("ERROR: Incorrect parameter block_SIZE > matrix_SIZE (%d > %d)\n", block_size, matrix_size);
      return ERR_USAGE_ARGC;
    }

  if (mode == 0 && argc != 6)
    {
      printf_main_process ("ERROR: Incorrect parameter MODE = %d without FILENAME\n", mode);
      return ERR_USAGE_ARGC;
    }

  size_args.set_args (matrix_size, block_size, print_size);
  return NO_ERROR;
}

void
check_errors (int ret, const char *progname, const char *filename)
{
  switch (ret)
    {
    case ERROR_CANNOT_OPEN_INPUT_FILE:
      printf_main_process ("%s : ERROR: Cannot open input file %s\n", progname, filename);
      break;
    case ERROR_CANNOT_READ_INPUT_FILE:
      printf_main_process ("%s : ERROR: Cannot read input file %s\n", progname, filename);
      break;
    case ERROR_INCORRECT_MATRIX_TYPE:
      printf_main_process ("%s : ERROR: Incorrect matrix type in %s\n", progname, filename);
      break;
    default:
      printf_main_process ("%s : ERROR: Unknown error %d in %s\n", progname, ret, filename);
    }
}
