#include "in_out.h"
#include "block_action.h"


void
reorganize_matrix (size_arguments &size_args, matr matrix, matr *ptr_columns)
{
  int sum = 0;

  for (int j = 0; j < size_args.block_lim; j++)
    {
      if (j % size_args.comm_size == size_args.my_rank)
        {
          ptr_columns[j / size_args.comm_size] = matrix + sum;
          sum += size_args.get_column_size (j);
        }
    }
}


/* ========================================= initialization ========================================= */
double
f (int s, int n, int i, int j)
{
  double ans = 0;
  i++; j++;

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
      ans = 1.0 / (i + j - 1);
      break;
    default:
      printf ("Unknown parameter %d for f\n", s);
    }
  return ans;
}

void
init_matrix (const int mode, size_arguments &size_args, matr *ptr_columns)
{
  int shift = 0, i, col_width;
  column_bl curr_column;

  for (int j_bl = 0; j_bl < size_args.block_lim; j_bl++)
    {
      col_width = size_args.get_col_width (j_bl);

      if (j_bl % size_args.comm_size == size_args.my_rank)
        {
          curr_column = ptr_columns[j_bl / size_args.comm_size];
          int i_lim = j_bl * size_args.block_size;
          for (i = 0; i < i_lim; i++)
            {
              for (int j = 0; j < col_width; j++)
                curr_column[j] = f (mode, size_args.matrix_size, i, j + shift);
              curr_column += col_width;
            }

          for (int k = 0; k < col_width; k++)
            for (int j = k; j < col_width; j++)
              curr_column[get_IND (j, k, col_width)] = f (mode, size_args.matrix_size, k + i, j + shift);
        }

      shift += size_args.block_size;
    }
}


/* ========================================= read ========================================= */
int read_array (FILE *fp, vect read_row, int size)
{
  for (int i = 0; i < size; i++)
    if (fscanf (fp, "%lf", read_row + i) != 1)
      {
        fclose (fp);
        fp = nullptr;
        return ERROR_CANNOT_READ_INPUT_FILE;
      }

  return NO_ERROR;
}

int
read_matrix (const char *filename, size_arguments &size_args, matr *ptr_columns)
{
  FILE *fp = nullptr;
  int err = NO_ERROR;

  if (size_args.my_rank == MAIN_PROCESS)
    {
      fp = fopen (filename, "r");
      if (!fp)
        err = ERROR_CANNOT_OPEN_INPUT_FILE;
    }

  MPI_Bcast (&err, 1, MPI_INT, MAIN_PROCESS, MPI_COMM_WORLD);
  if (err != NO_ERROR)
    return err;

  std::unique_ptr <double []> ptr_read_row;
  vect read_row = nullptr;

  if (size_args.my_rank == MAIN_PROCESS)
    {
      ptr_read_row = std::make_unique <double []> (size_args.matrix_size);
      read_row = ptr_read_row.get ();
    }

  for (int i = 0; i < size_args.print_size && err == NO_ERROR; i++)
    {
      if (size_args.my_rank == MAIN_PROCESS)
        err = read_array (fp, read_row, size_args.matrix_size);

      MPI_Bcast (&err, 1, MPI_INT, MAIN_PROCESS, MPI_COMM_WORLD);

      action_elem_row (i, size_args, ptr_columns, read_row, READ);
    }

  return err;
}


/* ========================================= print ========================================= */
void
print_matrix (size_arguments &size_args, matr *ptr_columns)
{
  std::unique_ptr <double []> ptr_printed_row;
  vect printed_row = nullptr;

  if (size_args.my_rank == MAIN_PROCESS)
    {
      ptr_printed_row = std::make_unique <double []> (size_args.matrix_size);
      printed_row = ptr_printed_row.get ();
    }

  for (int i = 0; i < size_args.print_size; i++)
    {
      action_elem_row (i, size_args, ptr_columns, printed_row, PRINT);

      if (size_args.my_rank == MAIN_PROCESS)
        {
          for (int j = 0; j < i; j++)
            printf ("     --    ");

          for (int j = i; j < size_args.print_size; j++)
            printf (" %10.3e", printed_row[j]);

          printf ("\n");
        }
    }
}

