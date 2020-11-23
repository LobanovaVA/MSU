#include "addition.h"

double
f (int n, int i, int j)
{
  return n - ((i > j) ? i : j);
}


int
read_matrix (double *data, int line_size, int column_size, const char *filename)
{
  FILE *fp;
  int i, j;
  double elem;

  fp = fopen (filename, "r");
  if (!fp) return ERROR_CANNOT_OPEN_INPUT_FILE;

  for (i = 0; i < line_size; i++)
    {
      for (j = 0; j < column_size; j++)
        {
          if (fscanf (fp, "%lf", &elem) != 1)
            {
              fclose (fp);
              return ERROR_CANNOT_READ_INPUT_FILE;
            }

          data[i * column_size + j] = elem;
        }
    }

  fclose (fp);
  return 0;
}


int
check_read_errors (int ret, const char *filename)
{
  if (ret < SUCCESS)
    {
      switch (ret)
        {
        case ERROR_CANNOT_OPEN_INPUT_FILE:
          printf ("ERROR: Cannot open input file %s\n", filename);
          break;
        case ERROR_CANNOT_READ_INPUT_FILE:
          printf ("ERROR: Cannot read %s\n", filename);
          break;
        default:
          printf ("ERROR: Unknown error %d in %s\n", ret, filename);
        }
      return ERR_INITIALIZATION;
    }
  return SUCCESS;
}


void
print_matrix (double *data, int line_size, int column_size)
{
  int line_lim, column_lim, i, j;
  line_lim = (MAX_PRINT < line_size) ? MAX_PRINT : line_size;
  column_lim = (MAX_PRINT < column_size) ? MAX_PRINT : column_size;

  for (i = 0; i < line_lim; i++)
    {
      for (j = 0; j < column_lim; j++)
        {
          //printf (" %f", data[i * column_size + j]);
          printf (" %10.3e", data[i * column_size + j]);
        }
      printf ("\n");
    }
}


void
init_matrix (double *matrix, int size)
{
  int i, j;
  for (i = 0; i < size; i++)
    for (j = 0; j < size; j++)
      matrix[i * size + j] = f (size, i, j);
}


void init_vector_X0 (double *vector, int size)
{
  int i;
  for (i = 0; i < size; i++)
    vector[i] = 1;
}


void
init_vector_B (double *vector, double *matrix, int size)
{
  int i, k;
  double sum;
  for (i = 0; i < size; i++)
    {
      sum = 0;
      for (k = 0; k < size; k += 2)
        {
          sum += matrix[i * size + k];
        }

      vector[i] = sum;
    }
}
