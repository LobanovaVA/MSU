#include "addition.h"

int
main (int argc, const char *argv[])
{
  int p, k, i, ret, total = 0;
  argument *args;
  pthread_t *tids;
  static pthread_barrier_t barrier;
  int *shared_num, *status, *result;
  double *shared_sum;
  bool get_total = true;

  if (argc < 2)
    {
      printf ("Usage: %s filename_1 ... filename_m\n", argv[0]);
      return ERROR_USAGE_ARGC;
    }

  p = argc - 1;

  ret = pthread_barrier_init (&barrier, nullptr, p);
  if (ret != 0)
    {
      perror ("ERROR: thread_barrier_init\n");
      return ERROR_PTHREAD_BARRIER_INIT;
    }

  /* === memory allocation === */
  args = new argument [p];
  if (!args)
    {
      perror ("ERROR: Can not allocate memory for args\n");
      return ERROR_ALLOCATE_MEMORY;
    }

  shared_sum = new double [p];
  if (!shared_sum)
    {
      perror ("ERROR: Can not allocate memory for shared_sum\n");
      delete [] args;
      return ERROR_ALLOCATE_MEMORY;
    }

  shared_num = new int [p];
  if (!shared_num)
    {
      perror ("ERROR: Can not allocate memory for shared_num\n");
      delete [] args;
      delete [] shared_sum;
      return ERROR_ALLOCATE_MEMORY;
    }

  status = new int [p];
  if (!status)
    {
      perror ("ERROR: Can not allocate memory for status\n");
      delete [] args;
      delete [] shared_sum;
      delete [] shared_num;
      return ERROR_ALLOCATE_MEMORY;
    }
  result = new int [p];
  if (!result)
    {
      perror ("ERROR: Can not allocate memory for result\n");
      delete [] args;
      delete [] shared_sum;
      delete [] shared_num;
      delete [] status;
      return ERROR_ALLOCATE_MEMORY;
    }


  /* === initialization === */
  for (k = 0; k < p; k++)
    {
      args[k].p = p;
      args[k].k = k;
      args[k].files = argv + 1;
      args[k].shared_sum = shared_sum;
      args[k].shared_num = shared_num;
      args[k].status = status;
      args[k].result = result;
      args[k].barrier = &barrier;
    }

  bzero (shared_sum, p * sizeof (double));
  bzero (shared_num, p * sizeof (int));
  bzero (status, p * sizeof (int));
  bzero (result, p * sizeof (int));


  /* === pthread === */
  tids =  new pthread_t[p];
  if (!tids)
    {
      perror ("ERROR: Cannot allocate tids\n");
      delete [] args;
      delete [] shared_sum;
      delete [] shared_num;
      delete [] status;
      delete [] result;
      return ERROR_ALLOCATE_MEMORY;
    }

  for (i = 1; i < p; i++)
    {
      ret = pthread_create (tids + i, nullptr, &thread_func, args + i);
      if (ret)
        {
          printf("ERROR: Cannot create pthread %d\n", i);
          delete [] args;
          delete [] shared_sum;
          delete [] shared_num;
          delete [] status;
          delete [] result;
          delete [] tids;
          return ERROR_PTHREAD_CREATE;
      }
  }

  thread_func (args + 0);


  /* === get total === */
  for (i = 1; i < p; i++)
    {
      if (status[i] != SUCCESS)
        {
          get_total = false;

          switch (status[i])
            {
            case ERROR_CANNOT_OPEN_INPUT_FILE:
              fprintf (stderr, "ERROR: Cannot open input file %s\n", argv[i + 1]);
              break;
            case ERROR_CANNOT_READ_INPUT_FILE:
              fprintf (stderr, "ERROR: Cannot read input file %s\n", argv[i + 1]);
              break;
            default:
              fprintf (stderr, "ERROR: Unknown error %d in %s\n", ret, argv[i + 1]);
            }
        }
    }

  if (get_total)
    {
      for (i = 0; i < p; i++)
          total += result[i];
      printf ("Answer = %d\n", total);
    }

  pthread_barrier_destroy (&barrier);
  delete [] args;
  delete [] shared_sum;
  delete [] shared_num;
  delete [] status;
  delete [] result;
  delete [] tids;
  return 0;
}
