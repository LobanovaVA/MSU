#include "addition.h"

int
main (int argc, char *argv[])
{
  const char *filename_A = 0, *filename_X0 = 0;
  double *matrix, *vector_X, *vector_X0;
  double time_solve, ans;
  int m, n, ret;


  /* === get args === */
  if (! ((argc == 3 || argc == 4 || argc == 5)
         && sscanf (argv[1], "%d", &m) == 1 && m >= 0
         && sscanf (argv[2], "%d", &n) == 1 && n > 0) )
    {
      printf ("ERROR: Usage: %s m n (a.txt) (x0.txt)\n", argv[0]);
      return ERR_USAGE_ARGC;
    }
  if (argc >= 4)
    filename_A = argv[3];
  if (argc == 5)
    filename_X0 = argv[4];


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
          return ERR_INITIALIZATION;
        }
    }
  else
    init_vector_X0 (vector_X0, n);

  printf("\nMatrix A:\n");
  print_matrix (matrix, n, n);
  printf("\nVector X_0:\n");
  print_matrix (vector_X0, n, 1);


  /* === solve === */
  time_solve = clock();
  ans = problem_1 (matrix, vector_X0, vector_X, m, n);
  time_solve = clock() - time_solve;

  printf ("\n====================\n\n");
  printf ("Answer: %10.3e\n", ans);
  printf ("Time:    %f\n", time_solve / CLOCKS_PER_SEC);
  printf("\nVector X_%d:\n", m);
  print_matrix (vector_X, n, 1);

  free (matrix);
  free (vector_X);
  free (vector_X0);
  return SUCCESS;
}

