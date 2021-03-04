#include "mpi.h"
#include "size_arguments.h"


void
size_arguments::set_args (int m_s, int bl_s, int pr_s)
{
  MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size (MPI_COMM_WORLD, &comm_size);

  matrix_size = m_s;
  block_size = bl_s;
  print_size = (pr_s < m_s) ? pr_s : m_s;

  mod = matrix_size % block_size;
  div = matrix_size / block_size;
  block_lim = div + (mod > 0);

  squared_block_size = block_size * block_size;
  buff_column_size = matrix_size * block_size;
}

int
size_arguments::get_col_width (int ind)
{
  if (ind == div)
    return mod;
  return block_size;
}

int
size_arguments::get_alloc_column_size (int ind)
{
  int res_size = 0;
  int col_width = get_col_width (ind);

  res_size += ind * block_size * col_width;
  res_size += (col_width * col_width + col_width) / 2;

  return res_size;
}

int
size_arguments::get_alloc_size ()
{
  int sum = 0;

  for (int j = 0; j < block_lim; j++)
    {
      if (j % comm_size == my_rank)
        sum += get_alloc_column_size (j);
    }

  return sum;
}

int
size_arguments::get_local_block_lim ()
{
  int bl_mod = block_lim % comm_size;
  int bl_div = block_lim / comm_size;

  return bl_div + (bl_mod > 0 && my_rank < bl_mod);
}

int
size_arguments::get_start_ind (int ind)
{
  if (ind % comm_size < my_rank)
    return ind - (ind % comm_size) + my_rank;
  else
    return ind - (ind % comm_size) + my_rank + comm_size;
}

