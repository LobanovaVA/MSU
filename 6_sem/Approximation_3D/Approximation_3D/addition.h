#ifndef ADDITION_H
#define ADDITION_H

#define LEN 1234
#define MAIN_TREAD 0

#define NO_ERR 0
#define ERR_USAGE_ARGC 2
#define ERR_DATA_INIT 4

#define ERROR_CANNOT_OPEN_INPUT_FILE -11
#define ERROR_CANNOT_READ_INPUT_FILE -12

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

#include <iostream>
#include <string.h>
#include <memory>

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

constexpr double EPS = 1.e-15;
constexpr int f_num_max = 8;

typedef double (*func) (double, double);

enum class Displayed_type
{
  etalon,
  approx,
  residual
};

enum class Message_type
{
  warning,
  information
};

inline bool
is_small (double value, double eps) { return fabs (value) < eps; }

void print_message (Message_type msg_t, const char *title_msg, const char *format, ...);

#endif // ADDITION_H
