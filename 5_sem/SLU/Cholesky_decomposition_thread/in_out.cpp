#include "in_out.h"


/* ========== initialization ========== */
double
f (int s, int n, int i, int j)
{
  double ans = 0;
  i++; j++;
  //my matrix must be symmetric
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

int
read_matrix (const char *filename, int matrix_size, matr matrix)
{
  FILE *fp;
  int i, j;
  double elem;

  fp = fopen (filename, "r");
  if (!fp) return ERROR_CANNOT_OPEN_INPUT_FILE;

  for (i = 0; i < matrix_size; i++)
    {
      for (j = 0; j < matrix_size; j++)
        {
          if (fscanf (fp, "%lf", &elem) != 1)
            {
              fclose (fp);
              return ERROR_CANNOT_READ_INPUT_FILE;
            }
          if (i <= j)
            matrix[get_IND (i, j, matrix_size)] = elem;
          else
            {
              if (!CMP(elem, matrix[get_IND (j, i, matrix_size)]))
                {
                  fclose (fp);
                  return ERROR_INCORRECT_MATRIX_TYPE;
                }
            }
        }
    }
  fclose (fp);
  return 0;
}

void
init_matrix (const int mode, int matrix_size, matr matrix)
{
  int i, j;
  for (i = 0; i < matrix_size; i++)
    for (j = i; j < matrix_size; j++)
      matrix[get_IND (i, j, matrix_size)] = f (mode, matrix_size, i, j);
}

void
init_vector_B (int matrix_size, matr matrix, vect vector_B)
{
  int i, k;
  double sum;
  for (i = 0; i < matrix_size; i++)
    {
      sum = 0;
      for (k = 0; k < matrix_size; k += 2)
        {
          sum += matrix[get_IND (i, k, matrix_size)];
        }
      vector_B[i] = sum;
    }
}


/* ========== thread initialization ========== */
void
init_thread (int matrix_size, int block_size, const int mode, char *filename,
             matr A, vect B, int th_p, int th_i, pthread_barrier_t *barrier, int *status)
{
  if (mode)
    init_matrix_thread (mode, matrix_size, block_size, A, th_p, th_i, barrier);
  else
    read_matrix_thread (filename, matrix_size, A, th_i, barrier, status);

  init_vector_B_thread (matrix_size, A, B, th_i, barrier);
  pthread_barrier_wait (barrier);
}

void
init_zero_thread (int matrix_size, int block_size, matr A, vect B, vect X, vect D, vect S,
                  int th_p, int th_i, pthread_barrier_t *barrier, int *status)
{
  int i, j, k;

  for (k = th_i * block_size; k < matrix_size; k += th_p * block_size)
    {
      for (j = k; j < matrix_size && j < k + block_size; j++)
        {
          for (i = 0; i <= j; i++)
            A[get_IND (i, j, matrix_size)] = 0;

          B[j] = 0;
          X[j] = 0;
          D[j] = 0;
          S[j] = 0;
        }

      for (; j < k + block_size; j++)
        S[j] = 0;
    }

  status[th_i] = SUCCESS;
  pthread_barrier_wait (barrier);
}


void
init_matrix_thread (const int mode, int matrix_size, int block_size, matr matrix,
                    int th_p, int th_i, pthread_barrier_t *barrier)
{
  int i, j, k;

  for (k = th_i * block_size; k < matrix_size; k += th_p * block_size)
    {
      for (j = k; j < matrix_size && j < k + block_size; j++)
        {
          for (i = 0; i <= j; i++)
            matrix[get_IND (i, j, matrix_size)] = f (mode, matrix_size, i, j);
        }
    }

  pthread_barrier_wait (barrier);
}

void
read_matrix_thread (const char *filename, int matrix_size, matr matrix,
                    int th_i, pthread_barrier_t *barrier, int *status)
{
  if (th_i == MAIN_THREAD)
    status[th_i] = read_matrix (filename, matrix_size, matrix);

  pthread_barrier_wait (barrier);
}

void
init_vector_B_thread (int matrix_size, matr matrix, vect vector_B,
                      int th_i, pthread_barrier_t *barrier)
{
  if (th_i == MAIN_THREAD)
    init_vector_B (matrix_size, matrix, vector_B);

  pthread_barrier_wait (barrier);
}




/* ========== print ========== */
void
print_matrix (double *data, int line_size, int column_size, int print_size)
{
  int line_lim, column_lim, i, j;
  line_lim = (print_size < line_size) ? print_size : line_size;
  column_lim = (print_size < column_size) ? print_size : column_size;

  for (i = 0; i < line_lim; i++)
    {
      for (j = 0; j < column_lim; j++)
        {
          printf (" %10.3e", data[i * column_size + j]);
        }
      printf ("\n");
    }
}

void
print_symmetric_matrix (matr matrix, int matrix_size, int print_size)
{
  int print_lim, i ,j;
  print_lim = (print_size < matrix_size) ? print_size : matrix_size;

  for (i = 0; i < print_lim; i++)
    {
      for (j = 0; j < print_lim; j++)
        {
          printf (" %10.3e", matrix[get_IND (i, j, matrix_size)]);
        }
      printf ("\n");
    }
}

void
print_upper_matrix (matr matrix, int matrix_size, int print_size)
{
  int print_lim, i ,j;
  print_lim = (print_size < matrix_size) ? print_size : matrix_size;

  for (i = 0; i < print_lim; i++)
    {
      for (j = 0; j < i; j++)
        {
          printf (" %10.3e", 0.0);
        }

      for (j = i; j < print_lim; j++)
        {
          printf (" %10.3e", matrix[get_IND (i, j, matrix_size)]);
        }
      printf ("\n");
    }
}



/* ========== thread print ========== */
void
print_after_init_thread (matr matrix, vect vector_B, int matrix_size,
                         int print_size, int th_i, pthread_barrier_t *barrier)
{
  if (th_i == MAIN_THREAD)
    {
      printf ("\nMatrix:\n");
      print_symmetric_matrix (matrix, matrix_size, print_size);
      printf ("\nVector B:\n");
      print_matrix (vector_B, matrix_size, 1, print_size);
    }

  pthread_barrier_wait (barrier);
}

void
print_after_solve_thread (vect vector_X, int matrix_size, int print_size,
                          int th_i, pthread_barrier_t *barrier)
{
  if (th_i == MAIN_THREAD)
    {
      printf ("\nVector X:\n");
      print_matrix (vector_X, matrix_size, 1, print_size);
    }

  pthread_barrier_wait (barrier);
}


void
print_time_thread (int th_i, double time_thread, double time_total,
                   pthread_barrier_t *barrier)
{
  if (th_i == MAIN_THREAD)
    {
      printf ("\nWall clock time: %.2f\n", time_total);
      printf ("\n|CPU| time |\n------------\n");
    }

  pthread_barrier_wait (barrier);
  printf ("|%3d| %5.2f|\n", th_i, time_thread);

  pthread_barrier_wait (barrier);
}



