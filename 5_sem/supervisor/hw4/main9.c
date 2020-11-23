#include "addition.h"

int
main (int argc, char *argv[])
{
  const char *filename_A = 0, *filename_X0 = 0;
  double *matrix, *vector_X, *vector_X0, *vector_B, *vector_R, *vector_W;
  double t, time_solve;
  int m, n, ret;


  /* === get args === */
  if (! ((argc == 4 || argc == 5 || argc == 6)
         && sscanf (argv[1], "%d", &m) == 1 && m >= 0
         && sscanf (argv[2], "%d", &n) == 1 && n > 0
         && sscanf (argv[3], "%lf", &t) == 1) )
    {
      printf ("ERROR: Usage: %s m n t (a.txt) (x0.txt)\n", argv[0]);
      return ERR_USAGE_ARGC;
    }
  if (argc >= 5)
    filename_A = argv[4];
  if (argc == 6)
    filename_X0 = argv[5];


  /* === memory allocation === */
  matrix = (double *) malloc (n * n * sizeof (double));
  if (!matrix)
    {
      printf ("ERROR: Can not allocate memory for matrix\n");
      return ERR_ALLOCATE_MEMORY;
    }

  vector_X = (double *) malloc (n * sizeof (double));
  if (!vector_X)
    {
      printf ("ERROR: Can not allocate memory for vector_X\n");
      free (matrix);
      return ERR_ALLOCATE_MEMORY;
    }

  vector_X0 = (double *) malloc (n * sizeof (double));
  if (!vector_X0)
    {
      printf ("ERROR: Can not allocate memory for vector_X0\n");
      free (matrix);
      free (vector_X);
      return ERR_ALLOCATE_MEMORY;
    }

  vector_B = (double *) malloc (n * sizeof (double));
  if (!vector_B)
    {
      printf ("ERROR: Can not allocate memory for vector_B\n");
      free (matrix);
      free (vector_X);
      free (vector_X0);
      return ERR_ALLOCATE_MEMORY;
    }

  vector_R = (double *) malloc (n * sizeof (double));
  if (!vector_R)
    {
      printf ("ERROR: Can not allocate memory for vector_R\n");
      free (matrix);
      free (vector_X);
      free (vector_X0);
      free (vector_B);
      return ERR_ALLOCATE_MEMORY;
    }

  vector_W = (double *) malloc (n * sizeof (double));
  if (!vector_W)
    {
      printf ("ERROR: Can not allocate memory for vector_R\n");
      free (matrix);
      free (vector_X);
      free (vector_X0);
      free (vector_B);
      free (vector_R);
      return ERR_ALLOCATE_MEMORY;
    }


  /* === initialization === */
  if (filename_A)
    {
      ret = read_matrix (matrix, n, n, filename_A);
      ret = check_read_errors (ret, filename_A);
      if (ret)
        {
          free (matrix);
          free (vector_X);
          free (vector_X0);
          free (vector_B);
          free (vector_R);
          free (vector_W);
          return ERR_INITIALIZATION;
        }
    }
  else
    init_matrix (matrix, n);

  if (filename_X0)
    {
      ret = read_matrix (vector_X0, n, 1, filename_X0);
      ret = check_read_errors (ret, filename_X0);
      if (ret)
        {
          free (matrix);
          free (vector_X);
          free (vector_X0);
          free (vector_B);
          free (vector_R);
          free (vector_W);
          return ERR_INITIALIZATION;
        }
    }
  else
    init_vector_X0 (vector_X0, n);

  init_vector_B (vector_B, matrix, n);

  printf("\nMatrix A:\n");
  print_matrix (matrix, n, n);
  printf("\nVector X_0:\n");
  print_matrix (vector_X0, n, 1);
  printf("\nVector B:\n");
  print_matrix (vector_B, n, 1);


  /* === solve === */
  time_solve = clock();
  problem_9 (matrix, vector_X0, vector_X, vector_B, vector_R, vector_W, t, m, n);
  time_solve = clock() - time_solve;

  printf ("\n============================\n\n");
  printf ("Sum |Ax - b|_i  = %10.3e\n", sum_Ax_b (matrix, vector_X, vector_B, n));
  printf ("Sum |x - x_mod| = %10.3e\n", sum_x_x0 (vector_X, n));
  printf ("Time:    %f\n", time_solve / CLOCKS_PER_SEC);
  printf("\nVector X_%d:\n", m);
  print_matrix (vector_X, n, 1);

  free (matrix);
  free (vector_X);
  free (vector_X0);
  free (vector_B);
  free (vector_R);
  free (vector_W);
  return SUCCESS;
}

