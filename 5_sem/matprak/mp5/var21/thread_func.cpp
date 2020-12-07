#include "addition.h"

void *
thread_func (void *data)
{
  argument *args = (argument *) data;
  int p, k, size;
  double *arr, *time;
  double *min_elem, *prev_first, *next_last;
  int *result;
  pthread_barrier_t * barrier;

  int i, l, r;
  double total_min;


  /* === preparing === */
  p = args -> p;
  k = args -> k;
  size = args -> size;
  arr = args -> arr;
  min_elem = args -> min_elem;
  prev_first = args -> prev_first;
  next_last = args -> next_last;
  result = args -> result;
  time = args -> time;
  barrier = args -> barrier;

  l = k * size;
  l /= p;
  r = (k + 1) * size;
  r /= p;


  /* === find min elem and init border elem === */
  time[k] = get_cpu_time ();
  find_min (arr, size, l, r, min_elem[k],
            prev_first[k], next_last[k], result[k]);
  pthread_barrier_wait (barrier);


  /* === get total min elem === */
  total_min = arr[0];
  for (i = 0; i < p; i++)
    {
      if (result[i] == SUCCESS)
        if (min_elem[i] < total_min)
          total_min = min_elem[i];
    }
  pthread_barrier_wait (barrier);


  /* === replace local min to total min elem === */
  replace_local_min (arr, size, l, r, total_min,
                     prev_first[k], next_last[k], result[k]);
  pthread_barrier_wait (barrier);


  time[k] = get_cpu_time () - time[k];
  pthread_barrier_wait (barrier);
  return nullptr;
}
