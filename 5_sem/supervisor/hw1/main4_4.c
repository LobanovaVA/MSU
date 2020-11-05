#include "all_func.h"

int main (int argc, char *argv[])
{
  int m_size, n_size, ret;
  char *file_name, *space;
  char **matrix;
  double time;

  if (argc != 5)
    {
      printf ("Usage: %s M N STR FILENAME\n", argv[0]);
      return -4;
    }
  m_size = atoi (argv[1]);
  n_size = atoi (argv[2]);
  space = argv[3];
  file_name = argv[4];

  if (m_size <= 0 || n_size <= 0)
    {
      printf ("Incorrect values M or N\n");
      return -5;
    }

  matrix = (char **) malloc (m_size * n_size * sizeof (char *));
  if (!matrix)
    {
      printf ("Not enough memory for matrix\n");
      return -6;
    }

  ret = read_str_matrix (file_name, matrix, m_size, n_size, space);
  if (ret < 0)
    {
      switch (ret)
        {
        case ERROR_CANNOT_OPEN_INPUT_FILE:
          printf ("Cannot open %s\n", file_name);
          break;
        case ERROR_CANNOT_READ_INPUT_FILE:
          printf ("Cannot read %s\n", file_name);
          break;
        case ERROR_NOT_ENOUGH_MEMMORY:
          printf ("Not enough memory\n");
          break;
        default:
          printf ("Unknown error %d in %s\n", ret, file_name);
        }
      free_matrix (matrix, m_size, n_size);
      return 1;
    }

  printf ("\nMATRIX:\n");
  print_str_matrix (matrix, m_size, n_size);

  time = clock ();
  quick_sort_str (matrix, m_size, n_size);
  time = (clock () - time) / CLOCKS_PER_SEC;

  printf ("\nMATRIX:_sort:\n");
  print_str_matrix (matrix, m_size, n_size);

  printf ("\nTime = %.4lf\n", time);
  free_matrix (matrix, m_size, n_size);
  return 0;
}
