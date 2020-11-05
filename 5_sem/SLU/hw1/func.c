#include "all_func.h"

double
f (int s, int n, int i, int j)
{
  double ans = 0;
  i++; j++;
  //my matrix must be symmetric
  switch (s)
    {
    case 1:
      ans = n - j + 1;
      break;
    case 2:
      ans = j;
      break;
    case 3:
      ans = j - i;
      break;
    case 4:
      ans = 1 / (i + j + 1);
      break;
    default:
      printf ("Unknown parameter %d for f\n", s);
    }
  return ans;
}


int
read_matrix (const char *file_name, int matrix_size, double *matrix)
{
  FILE *fp;
  int i, j;
  double elem;

  fp = fopen (file_name, "r");
  if (!fp) return ERROR_CANNOT_OPEN_INPUT_FILE;

  for (i = 0; i < matrix_size; i++)
    {
      for (j = 0; j < matrix_size; j++)
        {
          if (fscanf (fp, "%lf", &elem) != 1)
            {
              fclose (fp);
              return ERROR_CANNOT_READ_INPUT_FILE;
            }
          if (i <= j)
            matrix[get_IND (i, j, matrix_size)] = elem;
          else
            {
              if (!CMP(elem, matrix[get_IND (i, j, matrix_size)]))
                {
                  fclose (fp);
                  return ERROR_INCORRECT_MATRIX_TYPE;
                }
            }
        }
    }
  fclose (fp);
  return 0;
}

void
init_matrix (const int mode, int matrix_size, double *matrix)
{
  int i, j;
  for (i = 0; i < matrix_size; i++)
    for (j = i; j < matrix_size; j++)
      matrix[get_IND (i, j, matrix_size)] = f (mode, matrix_size, i, j);
}

void
print_matrix (double *data, int line_size, int column_size, int print_size)
{
  int line_lim, column_lim, i, j;
  line_lim = (print_size < line_size) ? print_size : line_size;
  column_lim = (print_size < column_size) ? print_size : column_size;

  for (i = 0; i < line_lim; i++)
    {
      for (j = 0; j < column_lim; j++)
        {
          printf (" [%d] %10.3e", i * column_size + j, data[i * column_size + j]);
        }
      printf ("\n");
    }
}

void
print_symmetric_matrix (double *matrix, int matrix_size, int print_size)
{
  int print_lim, i ,j;
  print_lim = (print_size < matrix_size) ? print_size : matrix_size;

  for (i = 0; i < print_lim; i++)
    {
      for (j = 0; j < print_lim; j++)
        {
          printf (" %10.3e", matrix[get_IND (i, j, matrix_size)]);
        }
      printf ("\n");
    }
}

void
init_vector_X (int matrix_size, double *vector_X)
{
  int i;
  for (i = 0; i < matrix_size; i++)
    {
      vector_X[i] = (double) ((i + 1) & 1);
    }
}

void
init_vector_B (int matrix_size,  double *matrix, double *vector_B)
{
  int i, k, sum;
  for (i = 0; i < matrix_size; i++)
    {
      sum = 0;
      for (k = 0; k < matrix_size; k += 2)
        {
          sum += matrix[get_IND (i, k, matrix_size)];
        }
      vector_B[i] = sum;
    }
}


double
diff_norm (int matrix_size, double *matrix, double *vector_B, double *vector_X)
{
  int i, k;
  double norm_B = 0, norm_Ax_B = 0, sum, elem_B;

  for (k = 0; k < matrix_size; k++)
    {
      sum = 0;
      elem_B = vector_B[k];

      for (i = 0; i < matrix_size; i++)
        {
          sum += matrix[get_IND (i, k, matrix_size)] * vector_X[i];
        }

      sum = fabs (sum - elem_B);
      if (sum > norm_Ax_B)
        norm_Ax_B = sum;
      if (elem_B > norm_B)
        norm_B = elem_B;
    }
  return norm_Ax_B / norm_B;
}

void
solve (int matrix_size, int block_size, double *matrix, double *vector_B, double *vector_X)
{
  init_vector_X (matrix_size, vector_X);
  (void) block_size;
  (void) matrix;
  (void) vector_B;
}
