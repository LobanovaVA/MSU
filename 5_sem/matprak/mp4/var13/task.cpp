#include "addition.h"

void
replace_inner (double *arr, int l, int r, double &b_sum, int &b_num,
               double &e_sum, int &e_num, int &border, int &result)
{
  int i, j, count;
  double sum, new_value;

  if (l == r)
    {
      b_num = e_num = 0;
      b_sum = e_sum = 0;
      result = 0;
      border = true;
      return;
    }

  b_num = e_num = 1;
  b_sum = arr[l];
  e_sum = arr[r - 1];
  result = 0;
  border = false;

  /* check tail from previous section*/
  for (i = l + 1; i < r; i++)
    {
      if (arr[i - 1] > arr[i])
        {
          b_num++;
          b_sum += arr[i];
        }
      else
        break;
    }

  /* check begin from following section */
  for (i = r - 1; i > l; i--)
    {
      if (arr[i - 1] > arr[i])
        {
          e_num++;
          e_sum += arr[i - 1];
        }
      else
        break;
    }

  /* this section is fully descending*/
  if (b_num == r - l && e_num == r - l)
    {
      border = true;
      return;
    }

  /* replace inner sections of decrease */
  for (i = l + b_num + 1; i < r - e_num; i++)
    {
      if (arr[i - 1] > arr[i])
        {
          sum = arr[i - 1];
          count = 1;

          for (j = i; arr[j - 1] > arr[j]; j++)
            {
              sum += arr[j];
              count++;
            }

          result += count;
          new_value = sum / count;

          for (j = 0; j < count; j++)
            arr[i + j - 1] = new_value;

          i += count - 1;
        }
    }

//  printf("l = %d, r = %d, b_num = %d, e_num = %d, b_sum = %f, e_sum = %f, result = %d, border = %d\n",
//         l, r, b_num, e_num, b_sum, e_sum, result, border);

}


