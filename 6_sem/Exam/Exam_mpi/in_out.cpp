#include "in_out.h"

double
f (int s, int n, int i)
{
  double ans = 0;

  switch (s)
    {
    case 1:
      ans = 1;
      break;
    case 2:
      ans = n - i;
      break;
    case 3:
      ans = i;
      break;
    case 4:
      ans = 1.0 / i;
      break;
    default:
      printf_main_process ("Unknown parameter %d for f\n", s);
    }
  return ans;
}

void
init_array (const int mode, const int size, array A)
{
  for (int i = 0; i < size; i++)
    A[i] = f (mode, size, i);
}

int
MPI_read_array (const char *filename, size_arguments &size_args, array A)
{
  FILE *fp = nullptr;
  int err = NO_ERROR;

  if (size_args.iam_main())
    {
      fp = fopen (filename, "r");
      if (!fp)
        err = ERROR_CANNOT_OPEN_INPUT_FILE;

      for (int i = 0; i < size_args.n_size && err == NO_ERROR; i++)
        if (fscanf (fp, "%lf", A + i) != 1)
          err = ERROR_CANNOT_READ_INPUT_FILE;

      fclose (fp);
    }

  MPI_Bcast (&err, 1, MPI_INT, MAIN_PROCESS, MPI_COMM_WORLD);
  if (err != NO_ERROR)
    return err;

  MPI_Bcast (A, size_args.n_size, MPI_DOUBLE, MAIN_PROCESS, MPI_COMM_WORLD);
  return err;
}

void
MPI_print_array (size_arguments &size_args, array A, process_type print_by)
{
  if (print_by == MAIN && size_args.my_rank != MAIN_PROCESS)
    return;

  for (int i = 0; i < PRINT_LIM && i < size_args.n_size; i++)
    printf (" %10.3e", A[i]);

  printf ("\n");
}
