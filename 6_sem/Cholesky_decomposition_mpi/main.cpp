#include "addition.h"
#include "in_out.h"
#include "norm.h"
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

  std::unique_ptr <double []> uptr_matrix, uptr_vect_D,
      uptr_vect_B, uptr_vect_Y, uptr_buff_row;
  std::unique_ptr <double* []> uptr_columns;

  matr matrix, *ptr_columns;
  vect vect_D, vect_B, vect_Y;
  buff_ptr buff_row;

  size_arguments size_args;

  ret = get_args (argc, argv, size_args, mode);
  if (ret != NO_ERROR)
    return ret;


  // === memory allocation === //
  uptr_matrix = std::make_unique <double []> (size_args.get_alloc_size ());
  uptr_vect_D = std::make_unique <double []> (size_args.matrix_size);
  uptr_vect_B = std::make_unique <double []> (size_args.matrix_size);
  uptr_vect_Y = std::make_unique <double []> (size_args.matrix_size);
  uptr_buff_row = std::make_unique <double []> (size_args.matrix_size);
  uptr_columns = std::make_unique <double* []> (size_args.get_local_block_lim ());

  matrix = uptr_matrix.get ();
  vect_D = uptr_vect_D.get ();
  vect_B = uptr_vect_B.get ();
  vect_Y = uptr_vect_Y.get ();
  buff_row = uptr_buff_row.get ();
  ptr_columns = uptr_columns.get ();

  reorganize_matrix (size_args, matrix, ptr_columns);


  // === initialization === //
  if (mode == 0)
    {
      filename = argv[5];
      ret = MPI_read_matrix (filename, size_args, ptr_columns, buff_row);

      if (ret != NO_ERROR)
        {
          check_read_errors (ret, argv[0], filename);
          printf_main_process (" for s = %d n = %d m = %d\n",
                               mode, size_args.matrix_size, size_args.block_size);
          return ret;
        }
    }
  else
    init_matrix (mode, size_args, ptr_columns);

  MPI_init_vector (size_args, ptr_columns, vect_B, buff_row);

  printf_main_process ("\nMatrix A:\n");
  MPI_print_matrix (size_args, ptr_columns, buff_row, SYMM);
  printf_main_process ("\nVector B:\n");
  print_matrix(vect_B, size_args.matrix_size, 1, size_args.print_size, MAIN);


  // === solve === //
  double norm = MPI_norm_A (size_args, ptr_columns, buff_row);
  printf_main_process ("\nMatrix norm = %10.3e\n", norm);
  norm = (norm < 100) ? norm : 1;

  double time_solve = clock ();
  ret = MPI_solve (size_args, ptr_columns, vect_D, vect_B, vect_Y, buff_row, norm);
  time_solve = (clock () - time_solve) / CLOCKS_PER_SEC;

  if (ret != NO_ERROR)
    {
      check_solve_errors (ret, argv[0]);
      printf_main_process (" for s = %d n = %d m = %d\n",
                           mode, size_args.matrix_size, size_args.block_size);
      return ret;
    }


  // === finally === //
  printf_main_process ("\nVector X:\n");
  print_matrix (vect_Y, size_args.matrix_size, 1, size_args.print_size, MAIN);

  printf_main_process ("\n   Reinit matrix...\n");
  if (argc == 6)
    MPI_read_matrix (filename, size_args, ptr_columns, buff_row);
  else
    init_matrix (mode, size_args, ptr_columns);
  MPI_init_vector (size_args, ptr_columns, vect_B, buff_row);

  double residual = MPI_norm_Ax_b (size_args, ptr_columns, vect_B, vect_Y, buff_row);

  printf_main_process ("\n%s : residual = %e elapsed = %.2f for s = %d n = %d m = %d\n",
                       argv[0], residual, time_solve, mode, size_args.matrix_size, size_args.block_size);

  return NO_ERROR;
}


