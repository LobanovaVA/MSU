#ifndef THREAD_INFO_H
#define THREAD_INFO_H

#include "window/window.h"
#include "th_time.h"

class Window;

struct thread_info
{
  int nx;
  int ny;
  double eps;

  func f;
  Grid_info *grid;

  int th_p;
  int th_k;
  pthread_barrier_t *barrier;
  pthread_cond_t *cond;
  bool proceed;
  int *th_out;

  solver_data *data;
  Window *window;
};

void *pthread_func (void *arg);
void synchronize (Window *window, int th_p, int &th_out,
                  pthread_cond_t &cond_out);
void reduce_sum (int th_p, int *a, int n);

#endif // THREAD_INFO_H
