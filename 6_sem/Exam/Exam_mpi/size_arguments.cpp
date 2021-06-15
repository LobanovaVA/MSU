#include "mpi.h"
#include "size_arguments.h"

int
size_arguments::get_beg_ind (const int rank) const
{
  if (n_size >= comm_size)
    {
      int ind = n_size * rank;
      return ind / comm_size;
    }

  if (rank < n_size)
    return rank;

  return n_size;
}

int
size_arguments::get_end_ind (const int rank) const
{
  if (n_size >= comm_size)
    {
      int ind = n_size * (rank + 1);
      ind = ind / comm_size;
      return (ind < n_size) ? ind : n_size;
    }

  if (rank < n_size)
    return rank + 1;

  return n_size;
}

void
size_arguments::set_args (int n_s)
{
  MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size (MPI_COMM_WORLD, &comm_size);

  n_size = n_s;
  my_beg = get_beg_ind (my_rank);
  my_end = get_end_ind (my_rank);
}


