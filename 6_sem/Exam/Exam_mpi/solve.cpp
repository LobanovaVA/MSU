#include "solve.h"

int
solve (size_arguments &size_args, array A)
{
  // === find new value === //
  double sum = 0, total_sum = 0;

  for (int i = size_args.my_beg; i < size_args.my_end; i++)
    sum += A[i];

  MPI_Allreduce (&sum, &total_sum, 1,  MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

  double new_value = total_sum / size_args.n_size;
  printf_main_process ("\nNew_value = %10.3e\n", new_value);


  // === check elemets === //
  int count = 0, total_count = 0;
  if (size_args.my_beg != size_args.my_end)
    {
      int i1 = std::max (1, size_args.my_beg);
      int i2 = std::min (size_args.n_size - 1, size_args.my_end);

      double prev = A[i1 - 1], curr = A[i1], next;

      if (size_args.my_beg == 0 && is_small (A[0] - A[1], EPS))
        {
          A[0] = new_value;
          count++;
        }

      if (i1 < i2)
        {
          next = A[i1 + 1];

          for (int i = i1; i < i2; i++)
            {
              next = A[i + 1];
              if (check(prev, curr, next))
                {
                  A[i] = new_value;
                  count++;
                }

              prev = curr;
              curr = next;
            }
        }

      if (size_args.my_end == size_args.n_size && is_small (prev - curr, EPS))
        {
          A[size_args.my_end - 1] = new_value;
          count++;
        }
    }

  MPI_Allreduce (&count, &total_count, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
  printf_main_process ("\nChanged elements = %d\n", total_count);


  send_result (size_args, A);
  return NO_ERROR;
}

void send_result (size_arguments &size_args, array A)
{
  // === send final array to MAIN_PROCESS === //
  if (size_args.iam_main ())
    {
      MPI_Status st;
      for (int i = 1; i < size_args.comm_size; i++)
        MPI_Recv (A + size_args.get_beg_ind (i), size_args.get_end_ind (i) - size_args.get_beg_ind (i),
                  MPI_DOUBLE, i, TAG, MPI_COMM_WORLD, &st);
    }
  else
    {
      MPI_Send (A + size_args.my_beg, size_args.my_end - size_args.my_beg,
                MPI_DOUBLE, MAIN_PROCESS, TAG, MPI_COMM_WORLD);
    }
}


bool
check (double a /* a[k-1] */, double b /* a[k] */, double c /* a[k+1] */)
{
  if (is_small (b - a, EPS) || is_small (b - c, EPS))
    return true;

  return false;
}


