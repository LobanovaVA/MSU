#ifndef ADDITION_H
#define ADDITION_H

#define PRINT_LIM 10
#define TAG 0
#define MAIN_PROCESS 0

#define NO_ERROR 0
#define ERROR_EPS 1
#define ERR_USAGE_ARGC 2

#define ERROR_CANNOT_OPEN_INPUT_FILE -11
#define ERROR_CANNOT_READ_INPUT_FILE -12

#include "mpi.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <fenv.h>
#include <stdbool.h>
#include <stdarg.h>
#include <memory>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <sched.h>

#include "size_arguments.h"

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

constexpr double EPS = 1.e-15;

using array = double *;
enum process_type {ALL, MAIN};

bool is_small (double value, double eps);

void printf_main_process (const char *format, ...);

int get_args (const int argc, char **argv, size_arguments &size_args, int &mode);
void check_read_errors  (int ret, const char *progname, const char *filename);
void check_solve_errors (int ret, const char *progname);

#define CMP(a,b) (!((a) > (b) || (a) < (b)))

#endif // ADDITION_H
