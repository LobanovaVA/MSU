#ifndef ALL_FUNC_H
#define ALL_FUNC_H

#define LEN 1234

#define ERROR_CANNOT_OPEN_INPUT_FILE -11
#define ERROR_CANNOT_READ_INPUT_FILE -12
#define ERROR_INCORRECT_MATRIX_TYPE -13
#define ERROR_NOT_ENOUGH_MEMMORY -21

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <fenv.h>

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

#define SIZE(n) ((((n) + 1) * (n)) >> 1)
#define CMP(a,b) (!((a) > (b) || (a) < (b)))

double f (int s, int n, int i, int j);
int read_matrix (const char *file_name, int matrix_size, double *matrix);
void init_matrix (const int mode, int matrix_size, double *matrix);
void print_matrix (double *data, int line_size, int column_size, int print_size);
void print_symmetric_matrix (double *matrix, int matrix_size, int print_size);

void init_vector_X (int matrix_size, double *vector_X);
void init_vector_B (int matrix_size,  double *matrix, double *vector_B);

double diff_norm (int matrix_size, double *matrix, double *vector_B, double *vector_X);
void solve (int matrix_size, int block_size, double *matrix, double *vector_B, double *vector_X);

#endif

