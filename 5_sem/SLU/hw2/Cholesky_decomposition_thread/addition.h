#ifndef ADDITION_H
#define ADDITION_H

#define LEN 1234

#define SUCCESS 0
#define ERR_USAGE_ARGC 2
#define ERR_ALLOCATE_MEMORY 3
#define ERR_DATA_INIT 4
#define ERR_PTHREAD_BARRIER_INIT 5
#define ERR_PTHREAD_CREATE 6

#define ERROR_CANNOT_OPEN_INPUT_FILE -11
#define ERROR_CANNOT_READ_INPUT_FILE -12
#define ERROR_INCORRECT_MATRIX_TYPE -13
#define ERROR_NOT_ENOUGH_MEMMORY -21
#define ERROR_SINGULAR_MATRIX_R -72

#define ERROR_EPS 1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <fenv.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sched.h>
#include <sys/sysinfo.h>
#include <pthread.h>

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

constexpr double EPS = 1.e-15;
using matr = double *;
using vect = double *;


class argument
{
public:
  int th_p = 0;
  int th_i = 0;
  int matrix_size = 0;
  int block_size = 0;
  int print_size = 0;

  int mode = 0;
  char *filename = 0;

  matr A = nullptr;
  vect B = nullptr;
  vect X = nullptr;
  vect D = nullptr;

  double time_thread = 0;
  double time_total = 0;

  pthread_barrier_t *barrier = nullptr;
  int *status = nullptr;

public:
  argument () = default;
  ~argument () = default;
};

void *thread_func (void *);

inline size_t
get_IND (size_t i, size_t j, size_t matrix_size)
{
  size_t first_ind, second_ind, pos;
  first_ind  = (i < j) ? i : j;
  second_ind = (i < j) ? j : i;
  pos = first_ind;
  pos = (pos * pos + pos) >> 1;
  return first_ind * matrix_size + second_ind - pos;
}

inline bool
is_small (double value, double eps)
{
  return fabs (value) < eps;
}

#define CMP(a,b) (!((a) > (b) || (a) < (b)))

#endif
