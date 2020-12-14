#include "solve.h"
#include "time.h"

void *
thread_func (void *data)
{
  char *filename;
  int matrix_size, block_size, print_size, mode;

  int th_p, th_i, nprocs;
  argument *args = (argument *) data;

  matr A;
  vect B, X, D, S;

  int *status;
  pthread_barrier_t * barrier;


  /* === preparing === */
  th_p = args -> th_p;
  th_i = args -> th_i;
  matrix_size = args -> matrix_size;
  block_size = args -> block_size;
  print_size = args -> print_size;

  mode = args -> mode;
  filename = args -> filename;

  A = args -> A;
  B = args -> B;
  X = args -> X;
  D = args -> D;
  S = args -> S;

  barrier = args -> barrier;
  status = args -> status;


  /* === set affinity === */
  cpu_set_t cpu;
  nprocs = get_nprocs();
  CPU_ZERO (&cpu);
  CPU_SET ((nprocs - 1 - th_i) % nprocs, &cpu);
  pthread_setaffinity_np (pthread_self (), sizeof (cpu), &cpu);
  pthread_barrier_wait (barrier);


  /* === initialization === */
  init_zero_thread (matrix_size, block_size, A, B, X, D, S, th_p, th_i, barrier, status);
  init_thread (matrix_size, block_size, mode, filename, A, B, th_p, th_i, barrier, status);

  if (status[MAIN_THREAD] != SUCCESS)
    return nullptr;

  print_after_init_thread (A, B, matrix_size, print_size, th_i, barrier);

  args -> time_thread = get_cpu_time ();
  args -> time_total = get_full_time ();


  /* === solve === */
  solve_thread (matrix_size, block_size, A, B, X, D, S, th_p, th_i, barrier, status);

  /* no barrier used because all threads get ERROR_EPS */
//  if (status[th_i] != SUCCESS)
//    return nullptr;

  for (int i = 0; i < th_p; i++)
    {
      if (status[i] != SUCCESS)
        {
          pthread_barrier_wait (barrier);
          return nullptr;
        }
    }

  args -> time_thread = get_cpu_time () - args -> time_thread;
  args -> time_total = get_full_time () - args -> time_total;

  print_after_solve_thread (X, matrix_size, print_size, th_i, barrier);


  /* === norm == */
  init_thread (matrix_size, block_size, mode, filename, A, B, th_p, th_i, barrier, status);
  norm_Ax_b_thread (matrix_size, A, B, X, th_p, th_i, barrier, args -> residual);

  /* === finally == */
  print_time_thread (th_i, args -> time_thread, args -> time_total, barrier);

  pthread_barrier_wait (barrier);
  return nullptr;
}
