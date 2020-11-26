#ifndef IN_OUT_H
#define IN_OUT_H

#include "addition.h"

double f (int s, int n, int i, int j);

int read_matrix (const char *file_name, int matrix_size, matr matrix);

void init_matrix (const int mode, int matrix_size, matr matrix);
void init_vector_B (int matrix_size,  matr matrix, vect vector_B);

void print_matrix (double *data, int line_size, int column_size, int print_size);
void print_symmetric_matrix (matr matrix, int matrix_size, int print_size);
void print_upper_matrix (matr matrix, int matrix_size, int print_size);

#endif

