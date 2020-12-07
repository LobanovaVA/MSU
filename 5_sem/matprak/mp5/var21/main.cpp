#include "addition.h"

int
main (int argc, const char *argv[])
{  
  argument *args;
  pthread_t *tids;
  int p, k, size;
  double *array, *min_elem, *prev_first, *next_last, *time;
  int *result;
  static pthread_barrier_t barrier;

  const char *filename = 0;
  int i, ret, total_res = 0;
  double full_time, sum_time = 0;


  /* === get args === */
  if (! ( (argc == 3 || argc == 4)
          && sscanf (argv[1], "%d", & size) == 1 && size > 0
          && sscanf (argv[2], "%d", & p) == 1 && p > 0 ))
    {
      printf ("ERROR: Usage: %s array_SIZE thread_NUM (FILENAME)\n", argv[0]);
      return ERR_USAGE_ARGC;
    }


  /* ==== array initialization === */
  array = new double [size];
  if (!array)
    {
      printf ("ERROR: Not enough memory for array\n");
      return ERR_ALLOCATE_MEMORY;
    }

  if (argc == 4)
    {
      filename = argv[3];
      ret = read_array (filename, array, size);
      ret = check_read_errors (ret, filename);
      if (ret)
        {
          delete [] array;
          return ERR_DATA_INIT;
        }
    }
  else
    init_array (array, size);

  printf ("\nOriginal = ");
  print_array (array, size);


  /* === memory allocation === */
  args = new argument [p];
  if (!args)
    {
      perror ("ERROR: Can not allocate memory for args\n");
      delete [] array;
      return ERR_ALLOCATE_MEMORY;
    }

  min_elem = new double [p];
  if (!min_elem)
    {
      perror ("ERROR: Can not allocate memory for min_elem\n");
      delete [] array;
      delete [] args;
      return ERR_ALLOCATE_MEMORY;
    }

  prev_first = new double [p];
  if (!prev_first)
    {
      perror ("ERROR: Can not allocate memory for prev_first\n");
      delete [] array;
      delete [] args;
      delete [] min_elem;
      return ERR_ALLOCATE_MEMORY;
    }

  next_last = new double [p];
  if (!next_last)
    {
      perror ("ERROR: Can not allocate memory for next_last\n");
      delete [] array;
      delete [] args;
      delete [] min_elem;
      delete [] prev_first;
      return ERR_ALLOCATE_MEMORY;
    }

  result = new int [p];
  if (!result)
    {
      perror ("ERROR: Can not allocate memory for result\n");
      delete [] array;
      delete [] args;
      delete [] min_elem;
      delete [] prev_first;
      delete [] next_last;
      return ERR_ALLOCATE_MEMORY;
    }

  time = new double [p];
  if (!time)
    {
      perror ("ERROR: Can not allocate memory for time\n");
      delete [] array;
      delete [] args;
      delete [] min_elem;
      delete [] prev_first;
      delete [] next_last;
      delete [] result;
      return ERR_ALLOCATE_MEMORY;
    }


  /* === initialization === */
  ret = pthread_barrier_init (&barrier, nullptr, p);
  if (ret != 0)
    {
      perror ("ERROR: thread_barrier_init\n");
      delete [] array;
      delete [] args;
      delete [] min_elem;
      delete [] prev_first;
      delete [] next_last;
      delete [] result;
      delete [] time;
      return ERR_PTHREAD_BARRIER_INIT;
    }

  for (k = 0; k < p; k++)
    {
      args[k].p = p;
      args[k].k = k;
      args[k].size = size;
      args[k].arr = array;
      args[k].min_elem = min_elem;
      args[k].prev_first = prev_first;
      args[k].next_last = next_last;
      args[k].result = result;
      args[k].time = time;
      args[k].barrier = &barrier;
    }

  bzero (min_elem, p * sizeof (double));
  bzero (prev_first, p * sizeof (double));
  bzero (next_last, p * sizeof (double));
  bzero (result, p * sizeof (int));
  bzero (time, p * sizeof (double));


  /* === pthread === */
  tids =  new pthread_t[p];
  if (!tids)
    {
      perror ("ERROR: Cannot allocate tids\n");
      delete [] array;
      delete [] args;
      delete [] min_elem;
      delete [] prev_first;
      delete [] next_last;
      delete [] result;
      delete [] time;
      pthread_barrier_destroy (&barrier);
      return ERR_ALLOCATE_MEMORY;
    }

  full_time = get_full_time ();

  for (i = 1; i < p; i++)
    {
      ret = pthread_create (tids + i, nullptr, &thread_func, args + i);
      if (ret)
        {
          printf("ERROR: Cannot create pthread %d\n", i);
          delete [] array;
          delete [] args;
          delete [] min_elem;
          delete [] prev_first;
          delete [] next_last;
          delete [] result;
          delete [] time;
          pthread_barrier_destroy (&barrier);
          return ERR_PTHREAD_CREATE;
        }
    }

  thread_func (args + 0);

  full_time = get_full_time () - full_time;


  /* === finally === */
  printf ("Result   = ");
  print_array (array, size);

  for (i = 0; i < p; i++)
    {
      sum_time += time[i];
      total_res += result[i];
    }

  printf ("\nAnswer: %d\n", total_res);
  printf ("\nWall clock time: %.2f\n", full_time);
  printf ("\nSum CPU time: %.2f\n", sum_time);

  printf ("\n|CPU| time |\n------------\n");
  for (i = 0; i < p; i++)
    printf ("|%3d| %5.2f|\n", i, time[i]);


  pthread_barrier_destroy (&barrier);
  delete [] array;
  delete [] args;
  delete [] min_elem;
  delete [] prev_first;
  delete [] next_last;
  delete [] result;
  delete [] time;
  delete [] tids;
  return 0;
}
