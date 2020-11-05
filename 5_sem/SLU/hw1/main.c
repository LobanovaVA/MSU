#include "all_func.h"

int
main (int argc, char *argv[])
{
  //feraiseexcept (FE_INVALID|FE_DIVBYZERO|FE_OVERFLOW);
  char *file_name;
  int matrix_size, block_size, print_size, mode;
  int ret;
  double *matrix, *vector_B, *vector_X;
  double time_solve, time_norm, ans_norm;

  if (! ( (argc == 5 || argc == 6)
          && sscanf (argv[1], "%d", & matrix_size) == 1 && matrix_size > 0
          && sscanf (argv[2], "%d", & block_size) == 1 && block_size > 0
          && sscanf (argv[3], "%d", & print_size) == 1 && print_size >= 0
          && sscanf (argv[4], "%d", & mode) == 1 && mode >= 0 && mode < 5 ))
    {
      printf ("Usage: %s matrix_SIZE block_SIZE print_SIZE MODE (FILENAME)\n", argv[0]);
      return -4;
    }

  if (mode == 0 && argc != 6)
    {
      printf ("Incorrect parameter MODE = %d without FILENAME\n", mode);
      return -5;
    }

  matrix = (double *) malloc (sizeof (double) * (((matrix_size + 1) * matrix_size) / 2) );
  if (!matrix)
    {
      printf ("Not enough memory for matrix\n");
      return -6;
    }

  if (argc == 6)
    {
      file_name = argv[5];
      ret = read_matrix (file_name, matrix_size, matrix);
      if (ret < 0)
        {
          switch (ret)
            {
            case ERROR_CANNOT_OPEN_INPUT_FILE:
              printf ("Cannot open %s\n", file_name);
              break;
            case ERROR_CANNOT_READ_INPUT_FILE:
              printf ("Cannot read %s\n", file_name);
              break;
            case ERROR_INCORRECT_MATRIX_TYPE:
              printf ("Incorrect matrix type in %s\n", file_name);
              break;
            default:
              printf ("Unknown error %d in %s\n", ret, file_name);
            }
          free (matrix);
          return 1;
        }
    }
  else
    init_matrix (mode, matrix_size, matrix);

  vector_B = (double *) malloc (sizeof (double) * matrix_size);
  if (!vector_B)
    {
      free (matrix);
      printf ("Not enough memory for vector_B\n");
      return -6;
    }
  vector_X = (double *) malloc (sizeof (double) * matrix_size);
  if (!vector_X)
    {
      free (matrix);
      free (vector_B);
      printf ("Not enough memory for vector_X\n");
      return -6;
    }

  init_vector_B (matrix_size, matrix, vector_B);

  printf ("\nMatrix:\n");
  print_symmetric_matrix (matrix, matrix_size, print_size);
  printf ("\nVector B:\n");
  print_matrix (vector_B, matrix_size, 1, print_size);

  time_solve = clock ();
  solve (matrix_size, block_size, matrix, vector_B, vector_X);
  time_solve = (clock () - time_solve) / CLOCKS_PER_SEC;

  printf ("\nVector X:\n");
  print_matrix (vector_X, matrix_size, 1, print_size);

  time_norm = clock ();
  ans_norm = diff_norm (matrix_size, matrix, vector_B, vector_X);
  time_norm = (clock () - time_norm) / CLOCKS_PER_SEC;

  printf ("\nTime solve = %.4lf", time_solve);
  printf ("\nTime norm  = %.4lf\n", time_norm);
  printf ("\nDiff norm  = %10.3e\n", ans_norm);

  printf ("\nReinit matrix...\n");
  if (argc == 6)
  {
    file_name = argv[5];
    read_matrix (file_name, matrix_size, matrix);
  }
  else
    init_matrix (mode, matrix_size, matrix);

  init_vector_B (matrix_size, matrix, vector_B);

  free (matrix);
  free (vector_B);
  free (vector_X);
  return 0;
}

