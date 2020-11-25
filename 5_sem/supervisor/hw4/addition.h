#ifndef ALL_FUNC_H
#define ALL_FUNC_H

#define MAX_PRINT 20
#define MAX_IT 1000000
#define MAX_IT_STEP 30
#define MAX_STEP 32
#define EPS 1e-16

#define SUCCESS 0
#define ERR_USAGE_ARGC 1
#define ERR_ALLOCATE_MEMORY 2
#define ERR_INITIALIZATION 3
#define ERR_SOLVE 4

#define ERROR_CANNOT_OPEN_INPUT_FILE -11
#define ERROR_CANNOT_READ_INPUT_FILE -12
#define ERROR_NOT_ENOUGH_MEMMORY -20

#define ERROR_SCALAR_PRODUCT -70
#define ERROR_SINGULAR -80

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>



// Initialization
double f (int n, int i, int j);
int read_matrix (double *data, int line_size, int column_size, const char *filename);
int check_read_errors (int ret, const char *filename);

void print_matrix (double *data, int line_size, int column_size);

void init_matrix (double *matrix, int size);
void init_vector_X0 (double *vector, int size);
void init_vector_B (double *vector, double *matrix, int size);



// Matrix operations
double sum_Ax_b (double *A, double *X, double *B, int size);
double sum_x_x0 (double *X, int size);

void Ax (double *A, double *X0, double *X, int size);
void Ax_b (double *A, double *X0, double *X, double *B, int size);
void AD_1x (double *A, double *X0, double *X, int size);

int culc_Lx (double *A, double *X, double *R, int n);
int culc_Rx (double *A, double *X, double *R, int n);


// Solve
double problem_1 (double *A, double *X0, double *X, int m, int n);
void problem_2 (double *A, double *X0, double *X, double *B, double t, int m, int n);

void problem_34 (double *A, double *X0, double *X, double *B, double *R, int m, int n,
                 void (*culc_Tk) (double *, double *, int, double *, double *));
void culc_Tk_3 (double *R, double *X, int n, double *ans_1, double *ans_2);
void culc_Tk_4 (double *R, double *X, int n, double *ans_1, double *ans_2);

void problem_5 (double *A, double *X0, double *X, double *B, double *R, int m, int n);
void problem_6 (double *A, double *X0, double *X, double *B, double *R, int m, int n);

void problem_7 (double *A, double *X0, double *X, double *B, double *R, double t, int m, int n);
void problem_8 (double *A, double *X0, double *X, double *B, double *R, double *W, double t, int m, int n);
void problem_9 (double *A, double *X0, double *X, double *B, double *R, double *W, double t, int m, int n);
void problem_10 (double *A, double *X0, double *X, double *B, double *R, double *W, double t, int m, int n);


/*
 * 3 - Steepest Descent
 * 7 - Jacobi
 * 8 - Gauss-Seidel
 * 9 - Inverse Gauss-Seidel
 * 10 - SSOR
*/

#endif

