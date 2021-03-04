#ifndef ADDITION_H
#define ADDITION_H

#define LEN 1234
#define TAG 0
#define MAIN_PROCESS 0

#define NO_ERROR 0
#define ERROR_EPS 1
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


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <fenv.h>
#include <stdbool.h>
#include <stdarg.h>
#include <memory>

#include "mpi.h"

#include "size_arguments.h"

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

constexpr double EPS = 1.e-15;


using matr = double *;
using vect = double *;
using matr_bl = double *;
using vect_bl = double *;
using column_bl = double *;
using buff_ptr = double *;


enum action_type {READ, PRINT};


int get_IND (int i, int j, int matrix_size);
bool is_small (double value, double eps);

void printf_main_process (const char *format, ...);

int get_args (const int argc, char **argv, size_arguments &size_args, int &mode);
void check_errors (int ret, const char *progname, const char *filename);


#define CMP(a,b) (!((a) > (b) || (a) < (b)))

#endif



