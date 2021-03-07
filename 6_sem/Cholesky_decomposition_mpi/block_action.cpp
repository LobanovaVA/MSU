#include "block_action.h"

#include "in_out.h"
void
MPI_action_elem_row (int ind, size_arguments &size_args, matr *ptr_columns, vect buff_row, action_type action)
{
  buff_ptr msg_place;

  int count, owner;
  int ind_bl = ind / size_args.block_size;
  int ind_bl_mult_block_size = ind_bl * size_args.block_size;

  if (action == GATHER)
    {
      owner = size_args.get_column_owner (ind_bl);
      if (size_args.my_rank == owner)
        {
          // === elements before diagonal === //
          msg_place = ptr_columns[ind_bl / size_args.comm_size];
          msg_place += ind % size_args.block_size;

          for (int j = 0; j < ind_bl_mult_block_size; j++)
            {
              if (owner == MAIN_PROCESS)
                buff_row [j] = *msg_place;
              else
                MPI_Send (msg_place, 1, MPI_DOUBLE, MAIN_PROCESS, TAG, MPI_COMM_WORLD);

              msg_place += size_args.get_col_width (ind_bl);
            }

          // === 1-st part elements of the diagonal block === //
          msg_place = ptr_columns[ind_bl / size_args.comm_size];
          msg_place += ind_bl_mult_block_size * size_args.get_col_width (ind_bl);

          for (int j = ind_bl_mult_block_size; j < ind; j++)
            {
              int shift = get_IND (j - ind_bl_mult_block_size, ind - ind_bl_mult_block_size, size_args.get_col_width(ind_bl));

              if (owner == MAIN_PROCESS)
                buff_row [j] = msg_place[shift];
              else
                MPI_Send (msg_place + shift, 1, MPI_DOUBLE, MAIN_PROCESS, TAG, MPI_COMM_WORLD);
            }
        }
      else if (size_args.my_rank == MAIN_PROCESS)
        for (int j = 0; j < ind; j++)
          MPI_Recv (buff_row + j, 1, MPI_DOUBLE, owner, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }


  // === 2-nd part elements of the diagonal block === //
  owner = size_args.get_column_owner (ind_bl);
  count = ind_bl_mult_block_size + size_args.get_col_width (ind_bl) - ind;

  if (size_args.my_rank == owner)
    {
      msg_place = ptr_columns[ind_bl / size_args.comm_size];
      msg_place += ind_bl_mult_block_size * size_args.get_col_width (ind_bl);
      msg_place += get_IND (ind - ind_bl_mult_block_size, ind - ind_bl_mult_block_size, size_args.get_col_width(ind_bl));

      switch(action)
        {
        case SCATTER:
          if (owner == MAIN_PROCESS)
            memcpy (msg_place, buff_row + ind, count * sizeof (double));
          else
            MPI_Recv (msg_place, count, MPI_DOUBLE, MAIN_PROCESS, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
          break;
        case GATHER:
          if (owner == MAIN_PROCESS)
            memcpy (buff_row + ind, msg_place, count * sizeof (double));
          else
            MPI_Send (msg_place, count, MPI_DOUBLE, MAIN_PROCESS, TAG, MPI_COMM_WORLD);
          break;
        }
    }
  else if (size_args.my_rank == MAIN_PROCESS)
    switch(action)
      {
      case SCATTER:
        MPI_Send (buff_row + ind, count, MPI_DOUBLE, owner, TAG, MPI_COMM_WORLD);  break;
      case GATHER:
        MPI_Recv (buff_row + ind, count, MPI_DOUBLE, owner, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE); break;
      }


  // === elements after diagonal === //
  for (int j_bl = ind_bl + 1; j_bl < size_args.block_lim; j_bl++)
    {
      owner = size_args.get_column_owner (j_bl);
      count = size_args.get_col_width (j_bl);

      if (size_args.my_rank == owner)
        {
          msg_place = ptr_columns[j_bl / size_args.comm_size];
          msg_place += ind * count; // count = size_args.get_col_width (j_bl);

          switch(action)
            {
            case SCATTER:
              if (owner == MAIN_PROCESS)
                memcpy (msg_place, buff_row + j_bl * size_args.block_size, count * sizeof (double));
              else
                MPI_Recv (msg_place, count, MPI_DOUBLE, MAIN_PROCESS, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
              break;

            case GATHER:
              if (owner == MAIN_PROCESS)
                memcpy (buff_row + j_bl * size_args.block_size, msg_place, count * sizeof (double));
              else
                MPI_Send (msg_place, count, MPI_DOUBLE, MAIN_PROCESS, TAG, MPI_COMM_WORLD);
              break;
            }
        }
      else if (size_args.my_rank == MAIN_PROCESS)
        switch(action)
          {
          case SCATTER:
            MPI_Send (buff_row + + j_bl * size_args.block_size, count, MPI_DOUBLE, owner, TAG, MPI_COMM_WORLD);
            break;

          case GATHER:
            MPI_Recv (buff_row + + j_bl * size_args.block_size, count, MPI_DOUBLE, owner, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            break;
          }
    }
}


// =========================================== get action =========================================== //
void
get_full_block (int i_bl, int s_bl, size_arguments &size_args, matr *ptr_columns, matr_bl R_bl)
{
  buff_ptr orig_R_bl = ptr_columns[s_bl / size_args.comm_size]
      + i_bl * size_args.get_col_width (s_bl) * size_args.block_size;

  if (s_bl != size_args.div)
    memcpy (R_bl, orig_R_bl, size_args.squared_block_size * sizeof (double));
  else //last block
    {
      memset (R_bl, 0, size_args.squared_block_size * sizeof (double));

      int col_width = size_args.get_col_width (s_bl);
      for (int i = 0; i < size_args.block_size; i++)
        {
          for (int j = 0; j < col_width; j++)
            R_bl[j] = orig_R_bl[j];

          R_bl += size_args.block_size;
          orig_R_bl += col_width;
        }
    }
}

void
get_diag_block (int i_bl, size_arguments &size_args, matr *ptr_columns, matr_bl R_bl)
{
  int col_width = size_args.get_col_width (i_bl);
  buff_ptr orig_R_bl = ptr_columns[i_bl / size_args.comm_size]
      + i_bl * col_width * size_args.block_size;

  if (i_bl == size_args.div)
    memset (R_bl, 0, size_args.mod * size_args.block_size * sizeof (double));

  for (int i = 0; i < col_width; i++)
    for (int j = 0; j < col_width; j++)
      R_bl[i * size_args.block_size + j] = orig_R_bl[get_IND (i, j, col_width)];
}

void
get_column (int j_bl, size_arguments &size_args, matr *ptr_columns, column_bl R_col)
{
  for (int i_bl = 0; i_bl < j_bl; i_bl++)
    {
      get_full_block (i_bl, j_bl, size_args, ptr_columns, R_col);
      R_col += size_args.squared_block_size;
    }

  get_diag_block (j_bl, size_args, ptr_columns, R_col);
}


// =========================================== put action =========================================== //
void
put_full_block (int i_bl, int s_bl, size_arguments &size_args, matr *ptr_columns, matr_bl R_bl)
{
  buff_ptr orig_R_bl = ptr_columns[s_bl / size_args.comm_size]
      + i_bl * size_args.get_col_width (s_bl) * size_args.block_size;

  if (s_bl != size_args.div)
    memcpy (orig_R_bl, R_bl, size_args.squared_block_size * sizeof (double));
  else //last block
    {
      int col_width = size_args.get_col_width (s_bl);
      for (int i = 0; i < size_args.block_size; i++)
        {
          for (int j = 0; j < col_width; j++)
            orig_R_bl[j] = R_bl[j];

          R_bl += size_args.block_size;
          orig_R_bl += col_width;
        }
    }
}

void
put_diag_block (int ind_bl, size_arguments &size_args, matr *ptr_columns, matr_bl R_i)
{
  int col_width = size_args.get_col_width (ind_bl);
  buff_ptr orig_R_i = ptr_columns[ind_bl / size_args.comm_size]
      + ind_bl * col_width * size_args.block_size;

  for (int i = 0; i < col_width; i++)
    for (int j = i; j < col_width; j++)
      orig_R_i[get_IND (i, j, col_width)] = R_i[i * size_args.block_size + j];
}



