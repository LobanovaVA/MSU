#include "norm.h"
#include "block_action.h"

double
MPI_norm_A (size_arguments &size_args, matr *ptr_columns)
{
  double norm = 0, sum;
  std::unique_ptr <double []> ptr_elem_row;
  vect elem_row = nullptr;

  if (size_args.my_rank == MAIN_PROCESS)
    {
      ptr_elem_row = std::make_unique <double []> (size_args.matrix_size);
      elem_row = ptr_elem_row.get ();
    }

  for (int i = 0; i < size_args.matrix_size; i++)
    {
      MPI_action_elem_row (i, size_args, ptr_columns, elem_row, GATHER);

      if (size_args.my_rank == MAIN_PROCESS)
        {
          sum = 0;
          for (int j = 0; j < size_args.matrix_size; j++)
            sum += fabs (elem_row[j]);

          if (sum > norm)
            norm = sum;
        }
    }

  MPI_Bcast (&norm, 1, MPI_DOUBLE, MAIN_PROCESS, MPI_COMM_WORLD);
  return norm;
}

double
MPI_norm_Ax_b (size_arguments &size_args, matr *ptr_columns, vect B, vect X)
{
  double norm, norm_B = 0, norm_Ax_B = 0, sum, elem_B;
  std::unique_ptr <double []> ptr_elem_row;
  vect elem_row = nullptr;

  if (size_args.my_rank == MAIN_PROCESS)
    {
      ptr_elem_row = std::make_unique <double []> (size_args.matrix_size);
      elem_row = ptr_elem_row.get ();
    }

  for (int i = 0; i < size_args.matrix_size; i++)
    {
      MPI_action_elem_row (i, size_args, ptr_columns, elem_row, GATHER);

      if (size_args.my_rank == MAIN_PROCESS)
        {
          sum = 0;
          elem_B = B[i];

          for (int j = 0; j < size_args.matrix_size; j++)
            sum += elem_row[j] * X[j];

          sum = fabs (sum - elem_B);
          if (sum > norm_Ax_B)
            norm_Ax_B = sum;

          elem_B = fabs (elem_B);
          if (elem_B > norm_B)
            norm_B = elem_B;
        }
    }

  if (size_args.my_rank == MAIN_PROCESS)
    norm = norm_Ax_B / norm_B;

  MPI_Bcast (&norm, 1, MPI_DOUBLE, MAIN_PROCESS, MPI_COMM_WORLD);
  return norm;
}

#if 0
double
MPI_norm_A (size_arguments &size_args, matr *ptr_columns)
{
  int col_width;
  double norm = 0, total_norm = 0, sum;
  buff_ptr curr_col = nullptr, curr_elem = nullptr;

  for (int ind_bl = 0; ind_bl < size_args.get_local_block_lim(); ind_bl++)
    {
      curr_col = ptr_columns[ind_bl];
      col_width = size_args.get_col_width (size_args.get_global_bl_ind (ind_bl));

      for (int loc_ind = 0; loc_ind < size_args.get_col_width (ind_bl); loc_ind++)
        {
          sum = 0;
          curr_elem = curr_col;

          for (int i = 0; i < size_args.get_global_bl_ind (ind_bl) + loc_ind; i++)
            {
              sum += fabs (*curr_elem);
              curr_elem += col_width;
            }

          if (sum > norm)
            norm = sum;

          curr_col++;
        }
    }

  MPI_Allreduce (&norm, &total_norm, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);
  return total_norm;
}
#endif
