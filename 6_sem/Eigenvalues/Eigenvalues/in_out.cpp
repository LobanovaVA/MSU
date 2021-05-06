#include "in_out.h"

/* ==================== initialization ==================== */
double
f (int s, int n, int i, int j)
{
  double ans = 0;
  i++; j++;
  //matrix must be symmetric j > i
  switch (s)
    {
    case 1:
      ans = n - j + 1;
      break;
      
    case 2:
      ans = 0;
      if (i == j)
        ans = 2;
      if (j - i == 1)
        ans = -1;
      break;
      
    case 3:
      ans = 0;
      if (i == j && j < n)
        ans = 1;
      if (i == n)
        ans = j;
      if (j == n)
        ans = i;
      break;
      
    case 4:
      ans = 1.0 / (i + j - 1);
      break;
      
    default:
      printf ("Unknown parameter %d for f\n", s);
    }
  return ans;
}


int
read_matrix (const char *file_name, int matrix_size, matr matrix)
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
              if (!CMP(elem, matrix[get_IND (j, i, matrix_size)]))
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
init_matrix (const int mode, int matrix_size, matr matrix)
{
  int i, j;
  for (i = 0; i < matrix_size; i++)
    for (j = i; j < matrix_size; j++)
      matrix[get_IND (i, j, matrix_size)] = f (mode, matrix_size, i, j);
}



/* ==================== print ==================== */
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
          printf (" %10.3e", data[i * column_size + j]);
        }
      printf ("\n");
    }
}

void
print_symmetric_matrix (matr matrix, int matrix_size, int print_size)
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
print_upper_matrix (matr matrix, int matrix_size, int print_size)
{
  int print_lim, i ,j;
  print_lim = (print_size < matrix_size) ? print_size : matrix_size;

  for (i = 0; i < print_lim; i++)
    {
      for (j = 0; j < i; j++)
        {
          printf (" %10.3e", 0.0);
        }

      for (j = i; j < print_lim; j++)
        {
          printf (" %10.3e", matrix[get_IND (i, j, matrix_size)]);
        }
      printf ("\n");
    }
}
