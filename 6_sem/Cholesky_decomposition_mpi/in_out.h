#ifndef IN_OUT_H
#define IN_OUT_H

#include "addition.h"

void reorganize_matrix (size_arguments &size_args, matr matrix, matr *ptr_columns);

double f (int s, int n, int i, int j);
void init_matrix (const int mode, size_arguments &size_args, matr *ptr_columns);

int read_array (FILE *fp, vect read_row, int size);
int read_matrix (const char *filename, size_arguments &size_args, matr *ptr_columns);

void print_matrix (size_arguments &size_args, matr *ptr_columns);

#endif
