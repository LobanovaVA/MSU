#include "block_action.h"

void
action_elem_row (int ind, size_arguments &size_args, matr *ptr_columns, vect buff_row, action_type action)
{
  MPI_Status status;
  buff_ptr msg_place;

  int count, owner;
  int ind_bl = ind / size_args.block_size;


  /* elements of the diagonal block */
  owner = ind_bl % size_args.comm_size;
  count = ind_bl * size_args.block_size + size_args.get_col_width (ind_bl) - ind;

  if (size_args.my_rank == owner)
    {
      msg_place = ptr_columns[ind_bl / size_args.comm_size];
      msg_place += ind_bl * size_args.block_size * size_args.get_col_width (ind_bl);
      msg_place += get_IND (ind - ind_bl * size_args.block_size, ind - ind_bl * size_args.block_size, size_args.block_size);

      switch(action)
        {
        case READ:
          if (owner == MAIN_PROCESS)
            memcpy (msg_place, buff_row + ind, count * sizeof (double));
          else
            MPI_Recv (msg_place, count, MPI_DOUBLE, MAIN_PROCESS, TAG, MPI_COMM_WORLD, &status);
          break;
        case PRINT:
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
      case READ:
        MPI_Send (buff_row + ind, count, MPI_DOUBLE, owner, TAG, MPI_COMM_WORLD);  break;
      case PRINT:
        MPI_Recv (buff_row + ind, count, MPI_DOUBLE, owner, TAG, MPI_COMM_WORLD, &status); break;
      }


  /* others elements */
  for (int j_bl = ind_bl + 1; j_bl < size_args.block_lim; j_bl++)
    {
      owner = j_bl % size_args.comm_size;
      count = size_args.get_col_width (j_bl);

      if (size_args.my_rank == owner)
        {
          msg_place = ptr_columns[j_bl / size_args.comm_size];
          msg_place += ind * count; // count = size_args.get_col_width (j_bl);

          switch(action)
            {
            case READ:
              if (owner == MAIN_PROCESS)
                memcpy (msg_place, buff_row + j_bl * size_args.block_size, count * sizeof (double));
              else
                MPI_Recv (msg_place, count, MPI_DOUBLE, MAIN_PROCESS, TAG, MPI_COMM_WORLD, &status);
              break;

            case PRINT:
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
          case READ:
            MPI_Send (buff_row + + j_bl * size_args.block_size, count, MPI_DOUBLE, owner, TAG, MPI_COMM_WORLD);
            break;

          case PRINT:
            MPI_Recv (buff_row + + j_bl * size_args.block_size, count, MPI_DOUBLE, owner, TAG, MPI_COMM_WORLD, &status);
            break;
          }
    }
}
