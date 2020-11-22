#ifndef ALL_FUNC_H
#define ALL_FUNC_H

#define MAX_PRINT 20
#define MAX_IT 1000000
#define MAX_IT_STEP 30
#define MAX_STEP 32
#define EPS 1e-16

#define SUCCESS 0
#define ERROR_USAGE_ARGC 1
#define ERROR_ALLOCATE_MEMORY 2
#define ERROR_INPUT_FILE 3
#define ERROR_SOLVE 4

#define ERROR_CANNOT_OPEN_INPUT_FILE -10
#define ERROR_CANNOT_READ_INPUT_FILE -20
#define ERROR_EMPTY_INPUT_FILE -30
#define ERROR_NOT_ENOUGH_MEMMORY -40

#define ERROR_NO_SOLUTION -70
#define ERROR_NO_SOLUTION_M4_1 -741
#define ERROR_NO_SOLUTION_M4_2 -742
#define ERROR_NO_SOLUTION_M5_1 -751
#define ERROR_NO_SOLUTION_M5_2 -752
#define ERROR_MAX_ITERATION -71
#define ERROR_MAX_STEP -73


//#define EQ(x,y) !((x) > (y) || (x) < (y))
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// Interpolation
int read_array(int size, double * arr, const char * filename);
void print_array (int size, double *arr);

double problem_1_1 (int size, double x0, double *arr_X, double *arr_Y);
double problem_1_2 (int size, double x0, double *arr_X, double *arr_Y);
double problem_1_3 (int size, double x0, double *arr_X, double *arr_Y, double *arr_D);


// Equations
double f (double x, int mode);
double d (double x, int mode);

int problem_2_1 (double a, double b, double eps, double *x, int mode);

int problem_2_2 (double x0, double eps, double *x, int mode);

int problem_2_3 (double a, double b, double eps, double *x, int mode);
int problem_2_4 (double a, double b, double eps, double *x, int mode);
int problem_2_5 (double a, double b, double eps, double *x, int mode);

int problem_2_6 (int m, double *arr, double a, double b, double eps, double *x, int mode);

int problem_2_7 (double x0, double e, double *x, int mode);

int problem_2_8 (double a, double b, double eps, double *x, int mode);
int problem_2_9 (double a, double b, double eps, double *x, int mode);
int problem_2_10 (double a, double b, double eps, double *x, int mode);


// Integrals
double problem_3_1 (double a, double b, int n, int mode);
double problem_3_2 (double a, double b, int n, int mode);

double problem_3_3 (double a, double b, int n, int mode);
double integral_3 (double x1, double x2, double f1, double f2);

double problem_3_4 (double a, double b, int n, int mode);
double integral_4 (double x1, double x2, double x3, double f1, double f2, double f3);

int problem_3_5 (double a, double b, double eps, double *r, int mode);
int problem_3_6 (double a, double b, double eps, double *r, int mode);

int problem_3_7 (double a, double eps, double *r, int mode);
int integral_7 (double a, double b, double eps, double *r, int mode);

int problem_3_8 (double a, double eps, double *r, int mode);
int integral_8 (double a, double b, double eps, double *r, int mode);

int problem_3_9 (double a, double b, double eps, double *r, int mode);
double x (double x, int mode);
double y (double x, int mode);

#endif

