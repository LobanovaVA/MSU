#include "addition.h"

bool
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
  int size;

  if (! ( (argc == 3 || argc == 4)
          && sscanf (argv[1], "%d", &size) == 1 && size > 0
          && sscanf (argv[2], "%d", &mode) == 1 && mode >= 0 && mode < 5))
    {
      printf_main_process ("ERROR: Usage: %s SIZE FORMULA (FILENAME)\n", argv[0]);
      return ERR_USAGE_ARGC;
    }

  if (mode == 0 && argc != 4)
    {
      printf_main_process ("ERROR: Incorrect parameter FORMULA = %d without FILENAME\n", mode);
      return ERR_USAGE_ARGC;
    }

  size_args.set_args (size);
  return NO_ERROR;
}


void
check_read_errors (int ret, const char *progname, const char *filename)
{
  switch (ret)
    {
    case ERROR_CANNOT_OPEN_INPUT_FILE:
      printf_main_process ("%s : ERROR: Cannot open input file %s", progname, filename);
      break;
    case ERROR_CANNOT_READ_INPUT_FILE:
      printf_main_process ("%s : ERROR: Cannot read input file %s", progname, filename);
      break;
    default:
      printf_main_process ("%s : ERROR: Unknown error %d in %s", progname, ret, filename);
    }
}

void
check_solve_errors (int ret, const char *progname)
{
  switch (ret)
    {
    case ERROR_EPS:
      printf_main_process ("%s : ERROR: Singular matrix R in Cholesky decomposition", progname);
      break;
    default:
      printf_main_process ("%s : ERROR: Unknown error %d", progname, ret);
    }
}
