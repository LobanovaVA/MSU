#include "addition.h"

int
main (int argc, const char *argv[])
{  
  argument *args;
  pthread_t *tids;
  int p, k, size_1, size_2;
  const char *filename = 0;

  std::unique_ptr <double []> ptr_matrix, ptr_prev_str, ptr_next_str,
      ptr_buff_str, ptr_shared_sum, ptr_time;
  std::unique_ptr <int []> ptr_shared_num;
  std::unique_ptr <argument []> ptr_args;
  std::unique_ptr <pthread_t []> ptr_tids;

  double *matrix, *prev_str, *next_str, *buff_str,  *shared_sum, *time;
  int *shared_num;
  static pthread_barrier_t barrier;

  int i, ret, total_res = 0;
  double full_time, sum_time = 0;


  /* === get args === */
  if (! ( (argc == 4 || argc == 5)
          && sscanf (argv[2], "%d", & size_1) == 1 && size_1 > 0
          && sscanf (argv[3], "%d", & size_2) == 1 && size_2 > 0
          && sscanf (argv[1], "%d", & p) == 1 && p > 0 ))
    {
      printf ("ERROR: Usage: %s thread_NUM matrix_SIZE_1 matrix_SIZE_2 (FILENAME)\n", argv[0]);
      return ERR_USAGE_ARGC;
    }

  if (p > size_1)
    {
      p = size_1;
      printf ("WARNING: change thread_NUM to %d\n", size_1);
    }

  /* ==== matrix initialization === */
  ptr_matrix = std::make_unique <double []> (size_1 * size_2);
  matrix = ptr_matrix.get ();

  if (argc == 5)
    {
      filename = argv[4];
      ret = read_matrix (filename, matrix, size_1, size_2);
      ret = check_read_errors (ret, filename);
      if (ret)
        return ERR_DATA_INIT;
    }
  else
    init_matrix (matrix, size_1, size_2);

  printf ("\nOriginal:\n");
  print_matrix (matrix, size_1, size_2);


  /* === memory allocation === */
  ptr_args = std::make_unique <argument []> (p);
  ptr_tids = std::make_unique <pthread_t []> (p);
  ptr_prev_str = std::make_unique <double []> (p * size_2);
  ptr_next_str = std::make_unique <double []> (p * size_2);
  ptr_buff_str = std::make_unique <double []> (p * size_2);
  ptr_shared_sum = std::make_unique <double []> (p);
  ptr_shared_num = std::make_unique <int []> (p);
  ptr_time = std::make_unique <double []> (p);

  args = ptr_args.get ();
  tids = ptr_tids.get ();
  prev_str = ptr_prev_str.get ();
  next_str = ptr_next_str.get ();
  buff_str = ptr_buff_str.get ();
  shared_sum = ptr_shared_sum.get ();
  shared_num = ptr_shared_num.get ();
  time = ptr_time.get ();


  /* === initialization === */
  ret = pthread_barrier_init (&barrier, nullptr, p);
  if (ret != SUCCESS)
    {
      perror ("ERROR: thread_barrier_init\n");
      return ERR_PTHREAD_BARRIER_INIT;
    }

  for (k = 0; k < p; k++)
    {
      args[k].p = p;
      args[k].k = k;
      args[k].size_1 = size_1;
      args[k].size_2 = size_2;
      args[k].matrix = matrix;

      args[k].prev_str = prev_str + k * size_2;
      args[k].next_str = next_str + k * size_2;
      args[k].buff_str = buff_str + k * size_2;
      args[k].shared_sum = shared_sum;
      args[k].shared_num = shared_num;

      args[k].time = time;
      args[k].barrier = &barrier;
    }

  bzero (prev_str, p * size_2 * sizeof (double));
  bzero (next_str, p * size_2 * sizeof (double));
  bzero (buff_str, p * size_2 * sizeof (double));
  bzero (shared_sum, p * sizeof (double));
  bzero (shared_num, p * sizeof (int));
  bzero (time, p * sizeof (double));


  /* === pthread === */
  full_time = get_full_time ();

  for (i = 1; i < p; i++)
    {
      ret = pthread_create (tids + i, nullptr, &thread_func, args + i);
      if (ret)
        {
          printf("ERROR: Cannot create pthread %d\n", i);
          pthread_barrier_destroy (&barrier);
          return ERR_PTHREAD_CREATE;
        }
    }

  thread_func (args + 0);

  full_time = get_full_time () - full_time;


  /* === finally === */
  printf ("\nResult:\n");
  print_matrix (matrix, size_1, size_2);

  for (i = 0; i < p; i++)
    {
      sum_time += time[i];
      total_res += shared_num[i];
    }

  printf ("\nAnswer: %d\n", total_res);
  printf ("\nWall clock time: %.2f\n", full_time);
  printf ("\nSum CPU time: %.2f\n", sum_time);

  printf ("\n|CPU| time |\n------------\n");
  for (i = 0; i < p; i++)
    printf ("|%3d| %5.2f|\n", i, time[i]);


  pthread_barrier_destroy (&barrier);
  return SUCCESS;
}
