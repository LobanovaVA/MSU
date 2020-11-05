#include "all_func.h"

int
rand_array (double *arr, int size)
{
  int i;
  srand (time (NULL));
  for (i = 0; i < size; i++)
    arr[i] = rand() / CLOCKS_PER_SEC;
  return 0;
}

int
read_array (const char *file_name, double *arr, int size)
{
  FILE *fp;
  int i;

  fp = fopen (file_name, "r");
  if (!fp) return ERROR_CANNOT_OPEN_INPUT_FILE;

  for (i = 0; i < size; i++)
    {
      if (fscanf (fp, "%lf", (arr + i)) != 1)
        {
          fclose (fp);
          return ERROR_CANNOT_READ_INPUT_FILE;
        }
    }

  fclose (fp);
  return 0;
}

void
print_array (double *arr, int size)
{
  int i, print_size;
  print_size = ((size > MAX_PRINT) ? MAX_PRINT : size);
  for (i = 0; i < print_size; i++)
    printf ("[%d]: %.6f\n", i, arr[i]);
}



// Problem 2_1
int
search_subserie (const char *file_name, double *arr, int size)
{
  FILE *fp;
  int fl = 0, j, i = 0, ans = 0, s = -1;
  double x;

  fp = fopen (file_name, "r");
  if (!fp)
    return ERROR_CANNOT_OPEN_INPUT_FILE;

  while (fscanf (fp, "%lf", &x) == 1)
    {

      if (!(x > arr[i] || x < arr[i]))
        {
          i++;
          if (i == size)
            {
              ans++;
              s = size - 1;
              fl = 0;
              i = 0;
            }
          else
            continue;
        }
      else
        {
          fl = 1;
          s = i;
          i = 0;
        }

      while (s >= 0)
        {
          for (j = 0, i = 0; j + fl < s; j++, i++)
            {
              if (arr[size - s + j] > arr[i] || arr[size - s + j] < arr[i])
                {
                  s--;
                  i = 0;
                  break;
                }
            }
          if (j + fl >= s)
            {
              if (fl)
                {
                  if (!(x > arr[i] || x < arr[i]))
                    {
                      i++;
                      fl = 0;
                      break;
                    }
                  else
                    {
                      s--;
                      i = 0;
                    }
                }
              else
                break;
            }
        }
    }

  if (!feof (fp))
    {
      fclose (fp);
      return ERROR_CANNOT_READ_INPUT_FILE;
    }

  fclose (fp);
  return ans;
}



// Problem 2_2
int
remove_less_x (double* arr, int size, double x)
{
  int k = 0, i;
  for (i = 0; i < size; i++)
    {
      if (arr[i] < x)
        k++;
      else
        arr[i - k] = arr[i];
    }
  return size - k;
}



// Problem 2_3
void
right_move_to_k (double *arr, int size, int k)
{
  int s, i, nod;
  double arr0;

  k %= size;
  if (!k) return;
  nod = gcd (size, k);

  for (s = nod - 1; s >= 0; s--)
    {
      arr0 = arr[(s + (size / nod - 1) * k) % size];
      for (i = size / nod - 1; i > 0; i--)
        arr[(s + i * k) % size] = arr[(s + (i - 1) * k) % size];
      arr[s] = arr0;
    }
}

int
gcd (int a, int b)
{
  while (a != b)
    {
      if (a > b) a = (a % b) ? a % b : b;
      if (b > a) b = (b % a) ? b % a : a;
    }
  return a;
}
