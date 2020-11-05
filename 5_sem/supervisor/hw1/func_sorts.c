#include "all_func.h"

void
check_sort (double *arr, int size)
{
  int i;
  for (i = 0; i < size - 1; i++)
    {
      if (arr[i] > arr[i+1])
        return;
    }
  printf ("OK\n");
}

void
swap (double *a, int i, int j)
{
  double tmp = a[j];
  a[j] = a[i];
  a[i] = tmp;
}


// Problem 3_1
int
bin_search (const double *arr, int size, double x)
{
  int left = 0, right = size - 1, center;

  if (arr[left] > x)
    return 0;
  if (arr[right] < x)
    return size;

  while (left <= right)
    {
      center = (left + right) / 2;
      if(arr[center] <= x)
        left = center + 1;
      else
        right = center - 1;
    }
  return left;
}



// Problem 3_2
void
merge (int size_1, int size_2, const double *arr_1, const double *arr_2, double *arr_ans)
{
  int i = 0, j = 0, k = 0;
  while ((i < size_1) && (j < size_2))
    {
      if (arr_1[i] < arr_2[j])
        {
          arr_ans[k] = arr_1[i];
          i++;
          k++;
        }
      else
        {
          arr_ans[k] = arr_2[j];
          j++;
          k++;
        }
    }

  while (i < size_1)
    {
      arr_ans[k] = arr_1[i];
      i++;
      k++;
    }

  while (j < size_2)
    {
      arr_ans[k] = arr_2[j];
      j++;
      k++;
    }
}



// Problem 3_3
int
lin_redbuild (double *arr, int size, double x)
{
  int left = 0, right = size - 1;
  while (left <= right)
    {
      for (; left < size && arr[left] < x; left++);
      for (; right > 0 && arr[right] > x; right--);
      if (left <= right)
        {
          swap (arr, left, right);
          left++;
          right--;
        }
    }
  return left;
}



// Problem 3_4
void
bin_insert_sort (double *arr, int size)
{
  int i, j, k;
  for (i = 1; i < size; i++)
    {
      j = bin_search (arr, i, arr[i]);
      for (k = i; k > j; k--)
        swap (arr, k, k - 1);
    }
}



// Problem 3_5
void
merge_sort (double *arr_1, double *arr_2, int size)
{
  double *tmp = NULL, *arr_tmp = arr_1;
  int tail_len = 0, i = 0,  len_part;
  for (len_part = 1; len_part < size; len_part <<= 1)
    {
      for (i = 0; (i + 2 * len_part) <= size; i += (len_part * 2))
        merge (len_part, len_part, arr_1 + i, arr_1 + len_part + i, arr_2 + i);

      merge (size - i - tail_len, tail_len, arr_1 + i, arr_1 + size - tail_len, arr_2 + i);
      tail_len = size - i;

      tmp = arr_1;
      arr_1 = arr_2;
      arr_2 = tmp;
    }
  if (arr_tmp != arr_1)
    {
      for (i = 0; i < size; i++)
        arr_2[i] = arr_1[i];
    }
}



// Problem 3_6
void
quick_sort (double *arr, int size)
{
  int pos;
  double elem;

  if(size < 2)
    return ;

  while(size > 2)
    {
      elem = arr[size / 2];
      pos = lin_redbuild (arr, size, elem);
      if(pos < size - pos)
        {
          quick_sort (arr, pos);
          arr += pos;
          size -= pos;
        }
      else
        {
          quick_sort (arr + pos, size - pos);
          size = pos;
        }
    }
  if (size == 2 && arr[size - 2] > arr[size - 1])
    swap (arr, size - 2, size - 1);
  return ;
}




// Problem 3_7
void
heap_sort (double *arr, int size)
{
  int i = 0;
  first_rebuild (arr, size);

  for(i = size - 1; i >= 0; i--)
    {
      swap (arr, i, 0);
      max_tree (arr, i, 0);
    }
}


void
first_rebuild (double* arr, int size)
{
  int i, k, c;
  double tmp;
  for (k = 1; k < size; k++)
    {
      for (c = k, i = (k - 1) >> 1; c > 0; i = (i - 1) >> 1)
        {
          if (!(arr[i] < arr[k]))
              break;
          c = i;
        }
      tmp = arr[k];
      for(i = k; i > c; i = (i - 1) >> 1)
          arr[i] = arr[(i - 1) >> 1];

      arr[c] = tmp;
    }
}


void
max_tree (double *arr, int size, int j){
  int mc;
  double tmp = arr[j];
  while ((j << 1) + 1 < size)
    {
      mc = (j << 1) + 1;
      if ((j << 1) + 2 < size && arr[(j << 1) + 2] > arr[mc])
        mc = (j << 1) + 2;
      if (arr[mc] > tmp)
        arr[j] = arr[mc];
      else
        break;
      j = mc;
    }
  arr[j] = tmp;

}
