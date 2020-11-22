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
void Ax (double *A, double *X0, double *X, int size);
void b_Ax (double *A, double *X0, double *X, double *B, int size);
double scalar_product (double *V, double *W, int size);

// Solve
double problem_1 (double *A, double *X0, double *X, int m, int n);
void problem_2 (double *A, double *X0, double *X, double *B, double t, int m, int n);
void problem_3 (double *A, double *X0, double *X, double *B, double *R, int m, int n);

#endif

