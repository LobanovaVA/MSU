#include "addition.h"

double
f (int i, int j)
{
  return (i > j) ? i - j : j - i;
}

int
read_matrix (const char *filename, double *matrix, int size_1, int size_2)
{
  FILE *fp;
  int i, j;

  fp = fopen (filename, "r");
  if (!fp)
    return ERROR_CANNOT_OPEN_INPUT_FILE;

  for (i = 0; i < size_1; i++)
    {
      for (j = 0; j < size_2; j++)
        {
          if (fscanf (fp, "%lf", matrix + i * size_2 + j) != 1)
            {
              fclose (fp);
              return ERROR_CANNOT_READ_INPUT_FILE;
            }
        }
    }

  fclose (fp);
  return SUCCESS;
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
      return ERR_DATA_INIT;
    }
  return SUCCESS;
}

void
init_matrix (double *matrix, int size_1, int size_2)
{
  int i, j;

  for (i = 0; i < size_1; i++)
      for (j = 0; j < size_2; j++)
        matrix[i * size_2 + j] = f (i, j);

}

void
print_matrix (double *matrix, int size_1, int size_2)
{
  int i, j;

  for (i = 0; i < size_1; i++)
    {
      for (j = 0; j < size_2; j++)
          printf ("%6.2f ", matrix[i * size_2 + j]);
      printf ("\n");
    }
}

void
get_line (int i, double *line, double *matrix, int size_1, int size_2)
{
  if (i < 0 || i == size_1)
    return;

  memcpy (line, matrix + i * size_2, size_2 * sizeof (double));
}








