#include "addition.h"
#include "in_out.h"
#include "solve.h"

int full_main (int argc, char **argv);

int
main (int argc, char **argv)
{
  feenableexcept (FE_INVALID|FE_DIVBYZERO|FE_OVERFLOW);

  MPI_Init (&argc, &argv);
  full_main (argc, argv);

  MPI_Finalize ();
  return NO_ERROR;
}

int
full_main (int argc, char **argv)
{
  char *filename = 0;
  int mode, ret;
  size_arguments size_args;

  ret = get_args (argc, argv, size_args, mode);
  if (ret != NO_ERROR)
    return ret;

  std::unique_ptr <double []> ptr_A = std::make_unique <double []> (size_args.n_size);
  array A = ptr_A.get ();


  // === initialization === //
  if (mode == 0)
    {
      filename = argv[3];
      ret = MPI_read_array (filename, size_args, A);

      if (ret != NO_ERROR)
        {
          check_read_errors (ret, argv[0], filename);
          printf_main_process (" for n = %d p = %d \n", size_args.n_size, size_args.comm_size);
          return ret;
        }
    }
  else
    init_array (mode, size_args.n_size, A);

  printf_main_process ("\nArray:\n");
  MPI_print_array (size_args, A);


  // === solve === //
  double time_solve = clock ();
  ret = solve (size_args, A);
  time_solve = (clock () - time_solve) / CLOCKS_PER_SEC;

  if (ret != NO_ERROR)
    {
      check_solve_errors (ret, argv[0]);
      printf_main_process (" for n = %d p = %d \n", size_args.n_size, size_args.comm_size);
      return ret;
    }


  // === finally === //
  printf_main_process ("\nResult:\n");
  MPI_print_array (size_args, A);

  double sum_time = 0;
  MPI_Allreduce (&time_solve, &sum_time, 1,  MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
  printf_main_process ("\nSum time = %.2f\n", sum_time);

  printf_main_process ("\nTime:\n");
  MPI_Barrier (MPI_COMM_WORLD);
  printf ("#%d %.2f\n", size_args.my_rank, time_solve);

  return NO_ERROR;
}


