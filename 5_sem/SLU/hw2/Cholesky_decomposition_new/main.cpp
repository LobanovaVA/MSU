#include "solve.h"

int
main (int argc, char *argv[])
{
  feenableexcept (FE_INVALID|FE_DIVBYZERO|FE_OVERFLOW);

  cpu_set_t cpu;
  CPU_ZERO (&cpu);
  CPU_SET (get_nprocs() - 1, &cpu);

  sched_setaffinity (getpid(), sizeof (cpu), &cpu);

  char *file_name;
  int matrix_size, block_size, print_size, mode, ret;
  double time_solve, time_residue, residue, diff_ans;
  matr matrix, block_R1, block_R2, block_Ri, block_A;
  vect vector_B, vector_X, vector_D, block_vector_D;


  /* === get args === */
  if (! ( (argc == 5 || argc == 6)
          && sscanf (argv[1], "%d", & matrix_size) == 1 && matrix_size > 0
          && sscanf (argv[2], "%d", & block_size) == 1 && block_size > 0
          && sscanf (argv[3], "%d", & print_size) == 1 && print_size >= 0
          && sscanf (argv[4], "%d", & mode) == 1 && mode >= 0 && mode < 5 ))
    {
      printf ("ERROR: Usage: %s matrix_SIZE block_SIZE print_SIZE MODE (FILENAME)\n", argv[0]);
      return -4;
    }

  if (mode == 0 && argc != 6)
    {
      printf ("ERROR: Incorrect parameter MODE = %d without FILENAME\n", mode);
      return -5;
    }


  /* === memory allocation and initialization === */
  matrix = new double [((matrix_size + 1) * matrix_size) / 2];
  if (!matrix)
    {
      printf ("ERROR: Not enough memory for matrix\n");
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
              printf ("ERROR: Cannot open %s\n", file_name);
              break;
            case ERROR_CANNOT_READ_INPUT_FILE:
              printf ("ERROR: Cannot read %s\n", file_name);
              break;
            case ERROR_INCORRECT_MATRIX_TYPE:
              printf ("ERROR: Incorrect matrix type in %s\n", file_name);
              break;
            default:
              printf ("ERROR: Unknown error %d in %s\n", ret, file_name);
            }
          delete[] matrix;
          return 1;
        }
    }
  else
    init_matrix (mode, matrix_size, matrix);

  vector_B = new double [matrix_size];
  if (!vector_B)
    {
      delete[] matrix;
      printf ("ERROR: Not enough memory for vector_B\n");
      return -6;
    }

  vector_X = new double [matrix_size];
  if (!vector_X)
    {
      delete[] matrix;
      delete[] vector_B;
      printf ("ERROR: Not enough memory for vector_X\n");
      return -6;
    }

  vector_D = new double [matrix_size];
  if (!vector_D)
    {
      delete[] matrix;
      delete[] vector_B;
      delete[] vector_X;
      printf ("ERROR: Not enough memory for vector_D\n");
      return -6;
    }

  block_R1 = new double [block_size * block_size];
  if (!block_R1)
    {
      delete[] matrix;
      delete[] vector_B;
      delete[] vector_X;
      delete[] vector_D;
      printf ("ERROR: Not enough memory for block_R1\n");
      return -6;
    }

  block_R2 = new double [block_size * block_size];
  if (!block_R2)
    {
      delete[] matrix;
      delete[] vector_B;
      delete[] vector_X;
      delete[] vector_D;
      delete[] block_R1;
      printf ("ERROR: Not enough memory for block_R2\n");
      return -6;
    }

  block_Ri = new double [block_size * block_size];
  if (!block_Ri)
    {
      delete[] matrix;
      delete[] vector_B;
      delete[] vector_X;
      delete[] vector_D;
      delete[] block_R1;
      delete[] block_R2;
      printf ("ERROR: Not enough memory for block_Ri\n");
      return -6;
    }

  block_A = new double [block_size * block_size];
  if (!block_A)
    {
      delete[] matrix;
      delete[] vector_B;
      delete[] vector_X;
      delete[] vector_D;
      delete[] block_R1;
      delete[] block_R2;
      delete[] block_Ri;
      printf ("ERROR: Not enough memory for block_A\n");
      return -6;
    }

  block_vector_D = new double [block_size];
  if (!block_vector_D)
    {
      delete[] matrix;
      delete[] vector_B;
      delete[] vector_D;
      delete[] vector_X;
      delete[] block_R1;
      delete[] block_R2;
      delete[] block_Ri;
      delete[] block_A;
      printf ("ERROR: Not enough memory for block\n");
      return -6;
    }

  init_vector_B (matrix_size, matrix, vector_B);

  printf ("\nMatrix:\n");
  print_symmetric_matrix (matrix, matrix_size, print_size);
  printf ("\nVector B:\n");
  print_matrix (vector_B, matrix_size, 1, print_size);


  /* === solve === */
  time_solve = clock ();
  ret = solve (matrix_size,block_size, matrix, vector_B, vector_D,
               vector_X, block_R1, block_R2, block_Ri, block_A, block_vector_D);
  time_solve = (clock () - time_solve) / CLOCKS_PER_SEC;

  /*
  for (int l = 0; l < matrix_size; l++)
    {
      for (int h = 0; h < l; h++) printf (" %10.3e", 0.0);
      for (int h = l; h < matrix_size; h++)
        {
          double sumRDR = 0;
          for (int k = 0; k <= l; k++)
            sumRDR += matrix[get_IND (k, l, matrix_size)] * vector_D[k] * matrix[get_IND (k, h, matrix_size)] ;
          //matrix[get_IND (l, h, matrix_size)] = sumRDR;
          printf (" %10.3e", sumRDR);
        }
      printf ("\n");
    }
  */

  //printf ("\nA_ans\n"); print_symmetric_matrix(matrix, matrix_size, matrix_size);
  //cholesky_symm_storage(matrix_size, matrix, vector_D, 1);


  //  printf ("\nD_ans\n"); print_matrix(vector_D, matrix_size, 1, matrix_size);
  //  printf ("\nR_ans\n"); print_upper_matrix(matrix, matrix_size, matrix_size);

  if (ret < SUCCESS)
    {
      switch (ret)
        {
        case ERROR_SINGULAR_MATRIX_A:
          printf ("\nERROR: Singular matrix A\n");
          break;
        case ERROR_SINGULAR_MATRIX_R:
          printf ("\nERROR: Singular matrix R in Cholesky decomposition\n");
          break;
        case ERROR_CALC_Y:
          printf ("\nERROR: Degenerate element in cuclulate vector Y\n");
          break;
        case ERROR_CALC_X:
          printf ("\nERROR: Degenerate element in cuclulate vector X\n");
          break;
        default:
          printf ("\nERROR: Unknown error = %d in solve\n", ret);
        }

      delete[] matrix;
      delete[] vector_B;
      delete[] vector_D;
      delete[] vector_X;
      delete[] block_R1;
      delete[] block_R2;
      delete[] block_Ri;
      delete[] block_A;
      delete[] block_vector_D;
      printf ("Time part of solve func = %.4f\n", time_solve);
      return -7;
    }



  printf ("\nVector ans:\n");
  print_matrix (vector_X, matrix_size, 1, print_size);

  printf ("\n   Reinit matrix...\n\n");
  if (argc == 6)
    {
      file_name = argv[5];
      read_matrix (file_name, matrix_size, matrix);
    }
  else
    init_matrix (mode, matrix_size, matrix);
  init_vector_B (matrix_size, matrix, vector_B);

  time_residue = clock ();
  residue = norm_Ax_b (matrix_size, matrix, vector_B, vector_X);
  time_residue = (clock () - time_residue) / CLOCKS_PER_SEC;
  diff_ans = norm_x_x0 (matrix_size, vector_X);

  printf ("Time solve func = %.4f\n", time_solve);
  printf ("Time culc norm  = %.4f\n", time_residue);
  printf ("Diff ans =%10.3e\n", diff_ans);
  printf ("%s : residual = %e elapsed = %.2f for s = %d n = %d m = %d\n",
          argv[0], residue, time_solve, mode, matrix_size, block_size);

  delete[] matrix;
  delete[] vector_B;
  delete[] vector_D;
  delete[] vector_X;
  delete[] block_R1;
  delete[] block_R2;
  delete[] block_Ri;
  delete[] block_A;
  delete[] block_vector_D;
  return 0;
}

