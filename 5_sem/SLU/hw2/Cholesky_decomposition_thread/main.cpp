#include "solve.h"
#include "time.h"

int
main (int argc, char *argv[])
{
  feenableexcept (FE_INVALID|FE_DIVBYZERO|FE_OVERFLOW);

  //  cpu_set_t cpu;
  //  CPU_ZERO (&cpu);
  //  CPU_SET (get_nprocs() - 1, &cpu);

  //  sched_setaffinity (getpid(), sizeof (cpu), &cpu);

  //  double full_time, time_solve, time_residue, residue, diff_ans;

  char *filename = 0;
  int matrix_size, block_size, print_size, mode, ret;
  double full_time;
  matr matrix_A;
  vect vector_B, vector_X, vector_D;

  int thread_num, th_i;
  argument *args;
  pthread_t *tids;
  int *status;
  static pthread_barrier_t barrier;


  /* === get args === */
  if (! ( (argc == 6 || argc == 7)
          && sscanf (argv[1], "%d", & matrix_size) == 1 && matrix_size > 0
          && sscanf (argv[2], "%d", & block_size) == 1 && block_size > 0
          && sscanf (argv[3], "%d", & thread_num) == 1 && thread_num > 0
          && sscanf (argv[4], "%d", & print_size) == 1 && print_size >= 0
          && sscanf (argv[5], "%d", & mode) == 1 && mode >= 0 && mode < 5 ))
    {
      printf ("ERROR: Usage: %s matrix_SIZE block_SIZE thread_NUM print_SIZE MODE (FILENAME)\n", argv[0]);
      return ERR_USAGE_ARGC;
    }

  if (mode == 0 && argc != 7)
    {
      printf ("ERROR: Incorrect parameter MODE = %d without FILENAME\n", mode);
      return ERR_USAGE_ARGC;
    }

  if (mode == 0)
    filename = argv[6];


  /* === memory allocation === */
  args = new argument [thread_num];
  if (!args)
    {
      perror ("ERROR: Can not allocate memory for args\n");
      return ERR_ALLOCATE_MEMORY;
    }

  matrix_A = new double [((matrix_size + 1) * matrix_size) / 2];
  if (!matrix_A)
    {
      delete [] args;
      perror ("ERROR: Not enough memory for matrix_A\n");
      return ERR_ALLOCATE_MEMORY;
    }

  vector_B = new double [matrix_size];
  if (!vector_B)
    {
      delete [] args;
      delete [] matrix_A;
      perror ("ERROR: Not enough memory for vector_B\n");
      return ERR_ALLOCATE_MEMORY;
    }

  vector_X = new double [matrix_size];
  if (!vector_X)
    {
      delete [] args;
      delete [] matrix_A;
      delete [] vector_B;
      perror ("ERROR: Not enough memory for vector_X\n");
      return ERR_ALLOCATE_MEMORY;
    }

  vector_D = new double [matrix_size];
  if (!vector_D)
    {
      delete [] args;
      delete [] matrix_A;
      delete [] vector_B;
      delete [] vector_X;
      perror ("ERROR: Not enough memory for vector_D\n");
      return ERR_ALLOCATE_MEMORY;
    }

  status = new int [thread_num];
  if (!status)
    {
      delete [] args;
      delete [] matrix_A;
      delete [] vector_B;
      delete [] vector_X;
      delete [] vector_D;
      perror ("ERROR: Not enough memory for status\n");
      return ERR_ALLOCATE_MEMORY;
    }


  /* === initialization === */
  ret = pthread_barrier_init (&barrier, nullptr, thread_num);
  if (ret != 0)
    {
      delete [] args;
      delete [] matrix_A;
      delete [] vector_B;
      delete [] vector_X;
      delete [] vector_D;
      delete [] status;
      perror ("ERROR: thread_barrier_init\n");
      return ERR_PTHREAD_BARRIER_INIT;
    }

  for (th_i = 0; th_i < thread_num; th_i++)
    {
      args[th_i].th_p = thread_num;
      args[th_i].th_i = th_i;
      args[th_i].matrix_size = matrix_size;
      args[th_i].block_size = block_size;
      args[th_i].print_size = print_size;

      args[th_i].mode = mode;
      args[th_i].filename = filename;

      args[th_i].A = matrix_A;
      args[th_i].B = vector_B;
      args[th_i].X = vector_X;
      args[th_i].D = vector_D;

      args[th_i].barrier = &barrier;
      args[th_i].status = status;
    }


  /* === pthread === */
  tids =  new pthread_t[thread_num];
  if (!tids)
    {
      delete [] args;
      delete [] matrix_A;
      delete [] vector_B;
      delete [] vector_X;
      delete [] vector_D;
      delete [] status;
      pthread_barrier_destroy (&barrier);
      perror ("ERROR: Cannot allocate tids\n");
      return ERR_ALLOCATE_MEMORY;
    }

  full_time = get_full_time ();

  for (th_i = 1; th_i < thread_num; th_i++)
    {
      ret = pthread_create (tids + th_i, nullptr, &thread_func, args + th_i);
      if (ret)
        {
          delete [] args;
          delete [] matrix_A;
          delete [] vector_B;
          delete [] vector_X;
          delete [] vector_D;
          delete [] status;
          pthread_barrier_destroy (&barrier);
          printf  ("ERROR: Cannot create pthread %d\n", th_i);
          return ERR_PTHREAD_CREATE;
        }
    }

  thread_func (args + 0);

  full_time = get_full_time () - full_time;

  /* === check errors === */
  for (th_i = 0; th_i < thread_num; th_i++)
    {
      if (status[th_i] != SUCCESS)
        {
          switch (status[th_i])
            {
            case ERROR_CANNOT_OPEN_INPUT_FILE:
              printf ("%s : ERROR: Cannot open input file %s", argv[0], filename);
              break;
            case ERROR_CANNOT_READ_INPUT_FILE:
              printf ("%s : ERROR: Cannot read input file %s", argv[0], filename);
              break;
            case ERROR_INCORRECT_MATRIX_TYPE:
              printf ("%s : ERROR: Incorrect matrix type in %s", argv[0], filename);
              break;
            case ERROR_EPS:
              printf ("%s : ERROR: Singular matrix R in Cholesky decomposition", argv[0]);
              break;
            default:
              printf ("%s : ERROR: Unknown error %d", argv[0], status[th_i]);
            }

          printf (" for s = %d n = %d m = %d p = %d\n", mode, matrix_size, block_size, thread_num);
          delete [] args;
          delete [] matrix_A;
          delete [] vector_B;
          delete [] vector_X;
          delete [] vector_D;
          delete [] status;
          delete [] tids;
          pthread_barrier_destroy (&barrier);
          return -1;
        }
    }

  /* === solve === */

  printf ("\n   Reinit matrix...\n\n");
  if (argc == 7)
    {
      read_matrix (filename, matrix_size, matrix_A);
    }
  else
    init_matrix (mode, matrix_size, matrix_A);
  init_vector_B (matrix_size, matrix_A, vector_B);

  double residue = norm_Ax_b (matrix_size, matrix_A, vector_B, vector_X);
  printf ("%s : residual = %e for s = %d n = %d m = %d p = %d\n",
          argv[0], residue, mode, matrix_size, block_size, thread_num);

  /*
  time_solve = clock ();
  ret = solve (matrix_size,block_size, matrix, vector_B, vector_D,
               vector_X, block_R1, block_R2, block_Ri, block_A, block_vector_D);
  time_solve = (clock () - time_solve) / CLOCKS_PER_SEC;


  if (ret != SUCCESS)
    {
      switch (ret)
        {
        case ERROR_SINGULAR_MATRIX_R:
          printf ("\nERROR: Singular matrix R in Cholesky decomposition\n");
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
      filename = argv[5];
      read_matrix (filename, matrix_size, matrix);
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
*/

  printf ("Она любила писать пустые программы\n");
  delete [] args;
  delete [] matrix_A;
  delete [] vector_B;
  delete [] vector_X;
  delete [] vector_D;
  delete [] status;
  delete [] tids;
  pthread_barrier_destroy (&barrier);

  return SUCCESS;
}

