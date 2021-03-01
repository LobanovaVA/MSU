#include "in_out.h"
#include "size_arguments.h"

int
main (int argc, char *argv[])
{
  feenableexcept (FE_INVALID|FE_DIVBYZERO|FE_OVERFLOW);

  int source, dest, tag = 0;
  char message[LEN];
  MPI_Status status;

  char *filename = 0;
  int mode, ret;

  std::unique_ptr <double []> uptr_matrix;
  std::unique_ptr <double* []> uptr_columns;
  matr matrix, *ptr_columns;

  size_arguments size_args;

  /* === get args === */
  MPI_Init (&argc, &argv);

  ret = get_args (argc, argv, size_args, mode);
  if (ret != NO_ERROR)
    {
      MPI_Finalize ();
      return 0;
    }


  /* === memory allocation === */
  uptr_matrix = std::make_unique <double []> (size_args.get_alloc_size ());
  uptr_columns = std::make_unique <double* []> (size_args.get_local_block_lim ());

  matrix = uptr_matrix.get ();
  ptr_columns = uptr_columns.get ();

  reorganize_matrix (size_args, matrix, ptr_columns);
  bzero (matrix, size_args.get_alloc_size ());


  /* === initialization === */
  if (mode == 0)
    {
      filename = argv[5];
      ret = read_matrix (filename, size_args, ptr_columns);

      if (ret != NO_ERROR)
        {
          check_errors (ret, argv[0], filename);
          MPI_Finalize ();
          return 0;
        }
    }
  else
    init_matrix (mode, size_args, ptr_columns);


  print_matrix (size_args, ptr_columns);

  MPI_Finalize ();
  return 0;
}


