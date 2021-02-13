#ifndef ADDITION_H
#define ADDITION_H

#define LEN 1234
#define SUCCESS 0
#define ERROR_CANNOT_OPEN_INPUT_FILE -11
#define ERROR_CANNOT_READ_INPUT_FILE -12
#define ERROR_INCORRECT_MATRIX_TYPE -13
#define ERROR_NOT_ENOUGH_MEMMORY -21

#define ERROR_EPS 1
#define ERROR_SINGULAR_MATRIX_R -72

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

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

constexpr double EPS = 1.e-15;
using matr = double *;
using vect = double *;

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
