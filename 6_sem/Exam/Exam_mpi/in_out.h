#ifndef IN_OUT_H
#define IN_OUT_H

#include "addition.h"

double f (int s, int n, int i, int j);
void init_array (const int mode, const int n_size, array A);
int  MPI_read_array (const char *filename, size_arguments &size_args, array A);
void MPI_print_array (size_arguments &size_args, array A, process_type print_by = MAIN);

#endif
