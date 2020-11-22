#include "addition.h"

void *
thread_func (void *data)
{
  argument *args = (argument *) data;
  const char **files;
  double *shared_sum;
  int *shared_num;
  int *status;
  int *result;
  int p, k, i;
  int num = 0;
  double sum = 0;

  p = args -> p;
  k = args -> k;
  files = args -> files;
  shared_sum= args -> shared_sum;
  shared_num = args -> shared_num;
  status = args -> status;
  result = args -> result;

  status[k] = count_sum_and_num (files[k], shared_sum + k, shared_num + k);

  pthread_barrier_wait (args -> barrier);

  for (i = 0; i < p; i++)
    {
      if (status[i] != SUCCESS)
          return nullptr;
    }

  for (i = 0; i < p; i++)
    {
      sum += shared_sum[i];
      num += shared_num[i];
    }

  if (num)
    result[k] = count_greater_than (files[k], sum / num);
  else
    result[k] = 0;

  pthread_barrier_wait (args -> barrier);
  return nullptr;
}
