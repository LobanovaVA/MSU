#include "addition.h"

double
f (int n, int i)
{
  (void) n;
  return i;
}

int
read_array (const char *filename, double *array, int size)
{
  FILE *fp;
  int i;

  fp = fopen (filename, "r");
  if (!fp) return ERROR_CANNOT_OPEN_INPUT_FILE;

  for (i = 0; i < size; i++)
    {
      if (fscanf (fp, "%lf", array + i) != 1)
        {
          fclose (fp);
          return ERROR_CANNOT_READ_INPUT_FILE;
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
init_array (double *array, int size)
{
  int i;
  for (i = 0; i < size; i++)

      array[i] = f (size, i);
}

void
print_array (double *array, int size)
{
  int i, print_lim;
  print_lim = (MAX_PRINT < size) ? MAX_PRINT : size;

  for (i = 0; i < print_lim; i++)
      printf ("%6.2f ", array[i]);

  if (MAX_PRINT < size)
    printf ("...");

  printf ("\n");
}

