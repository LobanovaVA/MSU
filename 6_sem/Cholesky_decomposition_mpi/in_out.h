#ifndef IN_OUT_H
#define IN_OUT_H

#include "addition.h"

void reorganize_matrix (size_arguments &size_args, matr matrix, matr *ptr_columns);

double f (int s, int n, int i, int j);
void init_matrix (const int mode, size_arguments &size_args, matr *ptr_columns);
void MPI_init_vector (size_arguments &size_args, matr *ptr_columns, vect B, buff_ptr elem_row);

int read_array (FILE *fp, vect read_row, int size);
int MPI_read_matrix (const char *filename, size_arguments &size_args, matr *ptr_columns, buff_ptr read_row);

void print_matrix (double *data, int line_size, int column_size, int print_size, process_type print_by = ALL);
void MPI_print_matrix (size_arguments &size_args, matr *ptr_columns, buff_ptr printed_row, matrix_type matr_t);

#endif
