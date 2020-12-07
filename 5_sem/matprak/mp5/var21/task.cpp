#include "addition.h"

void
find_min (double *arr, int size, int l, int r, double &min_elem,
          double &prev_first, double &next_last, int &result)
{
  int i;

  if (l == r)
    {
      min_elem = prev_first = next_last = 0;
      result = E_EMPTY;
      return;
    }

  result = SUCCESS;
  min_elem = arr[l];

  if (l != 0)
    prev_first = arr[l - 1];

  if (r != size)
    next_last = arr[r];

  for (i = l; i < r; i++)
    {
      if (arr[i] < min_elem)
          min_elem = arr[i];
    }
}

void
replace_local_min (double *arr, int size, int l, int r, double total_min,
                   double prev_first, double next_last, int &result)
{
  int i;
  double prev, next;
  result = 0;

  if (l == r)
    return;

  if (size == 1)
    {
      result++;
      return;
    }

  if (r - l == 1)
    {
      if ( (l == 0 || arr[l] <= prev_first) && (r == size || arr[l] <= next_last) )
        {
          arr[l] = total_min;
          result++;
        }
      return;
    }

  prev = arr[l];

  if (arr[l] <= arr[l + 1] && (l == 0 || arr[l] <= prev_first))
    {
      arr[l] = total_min;
      result++;
    }

  for (i = l + 1; i < r - 1; i++)
    {
      next = arr[i + 1];

      if (arr[i] <= prev && arr[i] <= next)
        {
          arr[i] = total_min;
          result++;
        }

      prev = arr[i];
    }

  if (arr[r - 1] <= prev && ( r == size || arr[r - 1] <= next_last))
    {
      arr[r - 1] = total_min;
      result++;
    }
}
