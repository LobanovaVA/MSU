#include "addition.h"

void *
thread_func (void *data)
{
  argument *args = (argument *) data;
  int p, k, size;
  double *arr, *time;
  double *b_sum, *e_sum;
  int *b_num, *e_num;
  int *border, *result;
  pthread_barrier_t * barrier;

  int i, l, r, count, count_prev, count_next;
  double sum, sum_prev, sum_next, new_value;


  /* === preparing === */
  p = args -> p;
  k = args -> k;
  size = args -> size;
  arr = args -> arr;
  b_sum = args -> tmp_sum;
  b_num = args -> tmp_num;
  e_sum = b_sum + p;
  e_num = b_num + p;
  border = args -> border;
  result = args -> result;
  time = args -> time;
  barrier = args -> barrier;

  l = k * size;
  l /= p;
  r = (k + 1) * size;
  r /= p;

  count = count_prev = count_next = 0;
  sum = sum_prev = sum_next = new_value = 0;

  /* === replace inner sections of decrease === */
  time[k] = get_cpu_time ();
  replace_inner (arr, l, r, b_sum[k], b_num[k],
                 e_sum[k], e_num[k], border[k], result[k]);
  pthread_barrier_wait (barrier);


  /* === gluing together of decreasing sections === */
  if (border[k])
    {
      sum = b_sum[k];
      count = b_num[k];

      if (k != 0)
        gluing_previous (arr, p, k, size, e_sum, e_num,
                         border, sum, count);

      if (k != p - 1)
        gluing_following (arr, p, k, size, b_sum, b_num,
                          border, sum, count);

      pthread_barrier_wait (barrier);

      if (count && count != 1)
        {
          result[k] += r - l;
          new_value = sum / count;
          for (i = l; i < r; i++)
            arr[i] = new_value;
        }
    }
  else
    {
      sum_prev = b_sum[k];
      count_prev = b_num[k];

      if (k != 0)
        gluing_previous (arr, p, k, size, e_sum, e_num,
                           border, sum_prev, count_prev);

      sum_next = e_sum[k];
      count_next = e_num[k];

      if (k != p - 1)
        gluing_following (arr, p, k, size, b_sum, b_num,
                            border, sum_next, count_next);

      pthread_barrier_wait (barrier);

      if (count_prev && count_prev != 1)
        {
          result[k] += b_num[k];
          new_value = sum_prev / count_prev;
          for (i = 0; i < b_num[k]; i++)
            arr[l + i] = new_value;
        }

      if (count_next && count_next != 1)
        {
          result[k] += e_num[k];
          new_value = sum_next / count_next;
          for (i = 0; i < e_num[k]; i++)
            arr[r - i - 1] = new_value;
        }
    }

  pthread_barrier_wait (barrier);

  time[k] = get_cpu_time () - time[k];

  pthread_barrier_wait (barrier);
  return nullptr;
}


void
gluing_previous (double *arr, int p, int k, int size, double *e_sum,
                 int *e_num, int *border, double &sum, int &count)
{
  int i;

  for (i = k; i > 0; i--)
    {

      if ((i * size) / p == 0)
        continue;

      if (arr[(i * size) / p] >= arr[(i * size) / p - 1])
        break;

      sum += e_sum[i - 1];
      count += e_num[i - 1];

      if (!border[i - 1])
        break;
    }
}


void
gluing_following (double *arr, int p, int k, int size, double *b_sum,
                  int *b_num, int *border, double &sum, int &count)
{
  int i;

  for (i = k + 1; i < p; i++)
    {

      if ((i * size) / p == 0)
        continue;

      if (arr[(i * size) / p] >= arr[(i * size) / p - 1])
        break;

      sum += b_sum[i];
      count += b_num[i];

      if (!border[i])
        break;
    }
}
