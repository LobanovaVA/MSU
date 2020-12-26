#include "addition.h"

void
count_sum_num (double *matrix, int size_1, int size_2, int l, int r,
               double *prev_str, double *next_str, double &sum, int &num)
{
  int j, z;
  double *ptr_next, *ptr_prev, *ptr_curr;
  double check = 0;

  if (l == r)
    {
      printf ("\nhgrefdhbgrvfecdkjhgfdsttuhygtrf\n");
    }

  for (z = l; z < r; z++)
    {
      if (z == 0 || z == size_1) // do NOT check 1-st and last str
        continue;

      /* === get data === */
      ptr_curr = matrix + z * size_2;

      if (z == l && z == r - 1)
        {
          ptr_prev = prev_str;
          ptr_next = next_str;
        }
      else
        {
          if (z == l || z == r - 1)
            {
              if (z == l)
                {
                  ptr_prev = prev_str;
                  ptr_next = matrix + (z + 1) * size_2;
                }

              if (z == r - 1)
                {
                  ptr_prev = matrix + (z - 1) * size_2;
                  ptr_next = next_str;
                }
            }

          else
            {
              ptr_prev = matrix + (z - 1) * size_2;
              ptr_next = matrix + (z + 1) * size_2;
            }
        }

      /* === check elems === */
      for (j = 0; j < size_2 - 1; j++) // do NOT check last elem in str
        {
          check = ptr_curr [j + 1]
              + ptr_prev[j] + ptr_prev[j + 1]
              + ptr_next[j] + ptr_next[j + 1];

          if (6 * ptr_curr[j] > check)
            {
              sum += ptr_curr[j];
              num++;
            }
        }

    }
}


void
replace_elem (double *matrix, int size_1, int size_2, int l, int r,
              double *prev_str, double *next_str, double *buff_str, double value)
{
  int j, z;
  double *ptr_next, *ptr_prev, *ptr_curr;
  double check = 0;

  if (l == r)
    {
      printf ("\nhgrefdhbgrvfecdkjhgfdsttuhygtrf\n");
    }

  for (z = l; z < r; z++)
    {
      if (z == 0 || z == size_1) // do NOT check 1-st and last str
        continue;

      /* === get data === */
      ptr_curr = matrix + z * size_2;

      if (z == l && z == r - 1)
        {
          ptr_prev = prev_str;
          ptr_next = next_str;
        }
      else
        {
          ptr_prev = prev_str;
          if (z == r - 1)
            ptr_next = next_str;
          else
            ptr_next = matrix + (z + 1) * size_2;
        }

      memcpy (buff_str, ptr_curr, size_2 * sizeof (double));

      /* === check elems === */
      for (j = 0; j < size_2 - 1; j++) // do NOT check last elem in str
        {
          check = ptr_curr [j + 1]
              + ptr_prev[j] + ptr_prev[j + 1]
              + ptr_next[j] + ptr_next[j + 1];

          if (6 * ptr_curr[j] > check)
            {
              ptr_curr[j] = value;
            }
        }

      memcpy (prev_str, buff_str, size_2 * sizeof (double));


    }
}

