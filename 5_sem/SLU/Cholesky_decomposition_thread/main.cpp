#include "solve.h"
#include "time.h"

int
main (int argc, char *argv[])
{
  feenableexcept (FE_INVALID|FE_DIVBYZERO|FE_OVERFLOW);

  char *filename = 0;
  int matrix_size, block_size, print_size, mode, ret;
  int thread_num, th_i;

  std::unique_ptr <double []> ptr_matr_A, ptr_vect_B, ptr_vect_X, ptr_vect_D, ptr_vect_S;
  matr matr_A;
  vect vect_B, vect_X, vect_D, vect_S;

  std::unique_ptr <argument []> ptr_args;
  std::unique_ptr <pthread_t []> ptr_tids;
  std::unique_ptr <int []> ptr_status;

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

  if (thread_num > (matrix_size + block_size - 1) / block_size)
    {
      thread_num = (matrix_size + block_size - 1) / block_size;
      printf ("WARNING: thread_NUM > block_SIZE - change thread_NUM to %d\n", thread_num);
    }


  /* === memory allocation === */
  ptr_args = std::make_unique <argument []> (thread_num);
  ptr_tids = std::make_unique <pthread_t []> (thread_num);
  ptr_status = std::make_unique <int []> (thread_num);

  ptr_matr_A = std::make_unique <double []> (((matrix_size + 1) * matrix_size) / 2);
  ptr_vect_B = std::make_unique <double []> (matrix_size);
  ptr_vect_X = std::make_unique <double []> (matrix_size);
  ptr_vect_D = std::make_unique <double []> (matrix_size);
  ptr_vect_S = std::make_unique <double []> (block_size * ((matrix_size + block_size - 1) / block_size));

  args = ptr_args.get ();
  tids = ptr_tids.get ();
  status = ptr_status.get ();

  matr_A = ptr_matr_A.get ();
  vect_B = ptr_vect_B.get ();
  vect_X = ptr_vect_X.get ();
  vect_D = ptr_vect_D.get ();
  vect_S = ptr_vect_S.get ();


  /* === initialization === */
  ret = pthread_barrier_init (&barrier, nullptr, thread_num);
  if (ret != 0)
    {
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

      args[th_i].A = matr_A;
      args[th_i].B = vect_B;
      args[th_i].X = vect_X;
      args[th_i].D = vect_D;
      args[th_i].S = vect_S;

      args[th_i].barrier = &barrier;
      args[th_i].status = status;
    }


  /* === pthread === */
  for (th_i = 1; th_i < thread_num; th_i++)
    {
      ret = pthread_create (tids + th_i, nullptr, &thread_func, args + th_i);
      if (ret)
        {
          pthread_barrier_destroy (&barrier);
          printf  ("ERROR: Cannot create pthread %d\n", th_i);
          return ERR_PTHREAD_CREATE;
        }
    }

  thread_func (args + 0);


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
          pthread_barrier_destroy (&barrier);
          return -1;
        }
    }

  printf ("\n%s : residual = %e elapsed = %.2f for s = %d n = %d m = %d p = %d\n",
          argv[0], args[0].residual, args[0].time_total, mode, matrix_size, block_size, thread_num);


  pthread_barrier_destroy (&barrier);
  return SUCCESS;
}
