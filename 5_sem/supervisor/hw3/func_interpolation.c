#include "all_func.h"

int
read_array(int size, double *arr, const char *filename)
{
  FILE *fp;
  int i;

  fp = fopen (filename, "r");
  if (!fp)
    return ERROR_CANNOT_OPEN_INPUT_FILE;

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
print_array (int size, double *arr)
{
  int i, print_size;
  print_size = ((size > MAX_PRINT) ? MAX_PRINT : size);
  for (i = 0; i < print_size; i++)
    printf ("[%d]: %.6f\n", i, arr[i]);
}


// Problem 1_1
double
problem_1_1 (int size, double x0, double *arr_X, double *arr_Y)
{
  int i, j;
  double g, sum = 0;

  for (i = 0; i < size; i++)
    {
      g = 1;
      for (j = 0; j < size; j++)
        {
          if (i != j)
            g = g * (x0 - arr_X[j]) / (arr_X[i] - arr_X[j]);
        }
      sum += g * arr_Y[i];
    }
  return sum;
}


// Problem 1_2
double
problem_1_2 (int size, double x0, double *arr_X, double *arr_Y)
{
  int i, j;
  double sum = 0;

  for (i = 1; i < size; i++)
    {
      for(j = size - 1; j >= i; j--)
        {
          arr_Y[j] = (arr_Y[j] - arr_Y[j-1]) /(arr_X[j] - arr_X[j-i]);
        }
    }

  for (i = size - 1; i > 0; i--)
    {
      sum += arr_Y[i];
      sum *= (x0 - arr_X[i - 1]);
    }
  return sum + arr_Y[0];
}


// Problem 1_3
double
problem_1_3 (int size, double x0, double *arr_X, double *arr_Y, double *arr_D)
{
  double res = 0;
  int i, j;

  for (j = size - 1; j > 0; j--)
    arr_Y[j] = (arr_Y[j] - arr_Y[j - 1])
             / (arr_X[j] - arr_X[j - 1]);

  for (i = 2; i < 2 * size; i++)
    {
      for (j = 2 * size - 1; j >= i; j--)
        {
          if (j & 1) //if (j % 2 != 0)
            arr_D[j / 2] =  (arr_D[j / 2] - arr_Y[j / 2])
                          / (arr_X[j / 2] - arr_X[(j - i) / 2]);
          else
            arr_Y[j / 2] =  (arr_Y[j / 2] - arr_D[j /2 - 1])
                          / (arr_X[j / 2] - arr_X[(j - i) / 2]);
        }
    }

  res = arr_D[size - 1];
  for (i = 2 * size - 2; i >= 0; i--)
    {
      if (!(i & 1)) //if (i % 2 == 0)
        res = res * (x0 - arr_X[i / 2]) + arr_Y[i / 2];
      else
        res = res * (x0 - arr_X[i / 2]) + arr_D[i / 2];
    }

  return res;
}



