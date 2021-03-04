#include "addition.h"
#include "in_out.h"
#include "solve.h"


int
main (int argc, char **argv)
{
  feenableexcept (FE_INVALID|FE_DIVBYZERO|FE_OVERFLOW);

  char *filename = 0;
  int mode, ret;

  std::unique_ptr <double []> uptr_matrix, uptr_vect_D;
  std::unique_ptr <double* []> uptr_columns;

  matr matrix, *ptr_columns;
  vect vect_D;

  size_arguments size_args;


  // === get args === //
  MPI_Init (&argc, &argv);

  ret = get_args (argc, argv, size_args, mode);
  if (ret != NO_ERROR)
    {
      MPI_Finalize ();
      return 0;
    }


  // === memory allocation === //
  uptr_matrix = std::make_unique <double []> (size_args.get_alloc_size ());
  uptr_vect_D = std::make_unique <double []> (size_args.matrix_size);
  uptr_columns = std::make_unique <double* []> (size_args.get_local_block_lim ());

  matrix = uptr_matrix.get ();
  vect_D = uptr_vect_D.get ();
  ptr_columns = uptr_columns.get ();

  reorganize_matrix (size_args, matrix, ptr_columns);

  // === initialization === //
  if (mode == 0)
    {
      filename = argv[5];
      ret = MPI_read_matrix (filename, size_args, ptr_columns);

      if (ret != NO_ERROR)
        {
          check_errors (ret, argv[0], filename);
          MPI_Finalize ();
          return 0;
        }
    }
  else
    init_matrix (mode, size_args, ptr_columns);

  printf_main_process ("\nMatrix:\n");
  MPI_print_matrix (size_args, ptr_columns);
  printf_main_process ("\nVector B:\n");

  ret = MPI_solve (size_args, ptr_columns, vect_D);
  if (ret != NO_ERROR)
    {
      MPI_Finalize ();
      return 0;
    }

  printf_main_process ("\nMatrix:\n");
  MPI_print_matrix (size_args, ptr_columns);
  if (size_args.my_rank == MAIN_PROCESS)
    {
      printf ("\nVector D\n");
      print_matrix(vect_D, 1, size_args.matrix_size, size_args.print_size);
    }

  MPI_Finalize ();
  return 0;
}


