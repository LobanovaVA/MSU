#include "addition.h"

void *
thread_func (void *data)
{
  argument *args = (argument *) data;
  int p, k, size_1, size_2;
  double *matrix, *time;
  double *prev_str, *next_str, *buff_str, *shared_sum;
  int *shared_num;
  pthread_barrier_t * barrier;

  int l, r, i, num = 0;
  double sum = 0;

  /* === preparing === */
  p = args -> p;
  k = args -> k;
  size_1 = args -> size_1;
  size_2 = args -> size_2;
  matrix = args -> matrix;

  prev_str = args -> prev_str;
  next_str = args -> next_str;
  buff_str = args -> buff_str;
  shared_sum = args -> shared_sum;
  shared_num = args -> shared_num;

  time = args -> time;
  barrier = args -> barrier;


  l = k * size_1;
  l /= p;
  r = (k + 1) * size_1;
  r /= p;


  /* === get additional data === */
  get_line (l - 1, prev_str, matrix, size_1, size_2);
  get_line (r, next_str, matrix, size_1, size_2);
  pthread_barrier_wait (barrier);

  /* === get sum and num for thread data === */
  time[k] = get_cpu_time ();
  count_sum_num (matrix, size_1, size_2, l, r,
                 prev_str, next_str, shared_sum[k], shared_num[k]);
  pthread_barrier_wait (barrier);

  /* === get total mean === */
  for (i = 0; i < p; i++)
    {
      sum += shared_sum[i];
      num += shared_num[i];
    }
  pthread_barrier_wait (barrier);

  /* === replace elems === */
  if (num)
    replace_elem (matrix, size_1, size_2, l, r,
                  prev_str, next_str, buff_str, sum / num);
  time[k] = get_cpu_time () - time[k];

  pthread_barrier_wait (barrier);
  return nullptr;
}
