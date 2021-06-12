#include "thread_info.h"
#include "approximation.h"

#include "msr_matr/msr_matr_ind.h"
void *
pthread_func (void *arg)
{
  thread_info *th_info = static_cast<thread_info *> (arg);
  auto window = th_info->window;
  int th_k = th_info->th_k;
  int th_p = th_info->th_p;

  while (th_info->proceed)
    {
      double t = get_time ();
      auto data  = th_info->data;
      double *result = (data->x).data ();

      Approximation solver (th_p, th_info->eps, (data->I).data (),
                            (data->A).data (), (data->rhs).data (), result,
                            (data->u).data (), (data->r).data (),
                            (data->v).data (), (data->buf).data (),
                            th_info->grid, th_info->f, th_info->barrier);

      if (th_k == MAIN_TREAD)
        solver.fill_carcass ();
      pthread_barrier_wait (th_info->barrier);

      solver.fill_matrix (th_k);
      pthread_barrier_wait (th_info->barrier);

      solver.fill_rhs (th_k);
      pthread_barrier_wait (th_info->barrier);

      solver.solve (th_k);
      t = get_time () - t;
      //printf ("%.2f\n", t);
      pthread_barrier_wait (th_info->barrier);

      if (th_k == MAIN_TREAD)
        window->set_answer (result);

      synchronize (window, th_p, *(th_info->th_out), *(th_info->cond));
    }

  return NO_ERR;
}


void
synchronize (Window *window, int th_p, int &th_out, pthread_cond_t &cond_out)
{
  static pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
  static pthread_cond_t cond_in = PTHREAD_COND_INITIALIZER;

  static int th_in = 0;

  pthread_mutex_lock (&m);

  th_in++;

  if (th_in >= th_p)
    {
      th_out = 0;
      pthread_cond_broadcast (&cond_in);
    }
  else
    {
      while (th_in < th_p)
        pthread_cond_wait (&cond_in, &m);
    }

  th_out++;

  if (th_out >= th_p)
    {
      th_in = 0;
      window->signal_calculation_completed ();
    }

  while (th_out <= th_p)
    pthread_cond_wait (&cond_out, &m);

  pthread_mutex_unlock (&m);
}


void
reduce_sum (int th_p, int *a, int n)
{
  static pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
  static pthread_cond_t cond_in = PTHREAD_COND_INITIALIZER;
  static pthread_cond_t cond_out = PTHREAD_COND_INITIALIZER;

  static int th_in = 0;
  static int th_out = 0;
  static int *p_a;

  int i = 0;

  if (th_p <= 1)
    return;

  pthread_mutex_lock (&m);

  if (!p_a)
    p_a = a;
  else
    {
      if (a)
        for (i = 0; i < n; i++)
          p_a[i] += a[i];
    }

  th_in++;

  if (th_in >= th_p)
    {
      th_out = 0;
      pthread_cond_broadcast (&cond_in);
    }
  else
    {
      while (th_in < th_p)
        pthread_cond_wait (&cond_in, &m);
    }

  if (p_a && p_a != a)
    {
      for (int i = 0; i < n; i++)
        {
          a[i] = p_a[i];
        }
    }

  th_out++;

  if (th_out >= th_p)
    {
      p_a = 0;
      th_in = 0;
      pthread_cond_broadcast (&cond_out);
    }
  else
    {
      while (th_out < th_p)
        pthread_cond_wait (&cond_out, &m);
    }

  pthread_mutex_unlock (&m);
}
