#include "msr_matr.h"

void  /* y = Ax */
matr_mult_vector (int matrix_size, double *A, int *I,
                  double *x, double *y, int p, int k,
                  pthread_barrier_t *barrier)
{
  int i1, i2;
  get_ind_thread (matrix_size, p, k, i1, i2);

  for (int i = i1; i < i2; i++)
    {
      double s = A[i] * x[i];
      int len = I[i + 1] - I[i];
      int pos = I[i];

      for (int j = 0; j < len; j++)
        s += A[pos + j] * x[I[pos + j]];

      y[i] = s;
    }

  pthread_barrier_wait (barrier);
}

void  /* solve Mv = r */
apply_precond_Jacobi (int matrix_size, double *A, int */*I*/,
                      double *r, double *v, int p, int k,
                      pthread_barrier_t *barrier)
{
  int i1, i2;
  get_ind_thread (matrix_size, p, k, i1, i2);

  for (int i = i1; i < i2; i++)
    v[i] = r[i] / A[i];

  pthread_barrier_wait (barrier);
}


void /* x -= t * y */
lin_comb_vector (int size, double *x, double *y, double t,
                 int p, int k, pthread_barrier_t *barrier)
{
  int i1, i2, i;
  get_ind_thread (size, p, k, i1, i2);

  for (i = i1; i < i2 - 7; i += 8)
    {
      x[i] -= y[i] * t;
      x[i + 1] -= y[i + 1] * t;
      x[i + 2] -= y[i + 2] * t;
      x[i + 3] -= y[i + 3] * t;
      x[i + 4] -= y[i + 4] * t;
      x[i + 5] -= y[i + 5] * t;
      x[i + 6] -= y[i + 6] * t;
      x[i + 7] -= y[i + 7] * t;
    }

  for (; i < i2; i++)
    x[i] -= y[i] * t;

  pthread_barrier_wait (barrier);
}

double
scalar_prod (int size, double *x, double *y, double *buf,
             int p, int k, pthread_barrier_t *barrier)
{
  int i1, i2, i;
  get_ind_thread (size, p, k, i1, i2);

  double s[8] = {0};

  for (i = i1; i < i2 - 7; i += 8)
    {
      s[0] += x[i] * y[i];
      s[1] += x[i + 1] * y[i + 1];
      s[2] += x[i + 2] * y[i + 2];
      s[3] += x[i + 3] * y[i + 3];
      s[4] += x[i + 4] * y[i + 4];
      s[5] += x[i + 5] * y[i + 5];
      s[6] += x[i + 6] * y[i + 6];
      s[7] += x[i + 7] * y[i + 7];
    }
  for (; i < i2; i++)
    s[0] += x[i] * y[i];

  buf[k] = 0;
  for (i = 0; i < 8; i++)
    buf[0] += s[i];

  pthread_barrier_wait (barrier);

  double ans = 0;
  for (int i = 0; i < p; i++)
    ans += buf[i];

  pthread_barrier_wait (barrier);
  return ans;
}
