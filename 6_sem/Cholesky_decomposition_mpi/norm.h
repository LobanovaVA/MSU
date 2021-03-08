#ifndef NORM_H
#define NORM_H

#include "addition.h"

double MPI_norm_A (size_arguments &size_args, matr *ptr_columns);

double MPI_norm_Ax_b (size_arguments &size_args, matr *ptr_columns, vect B, vect X);

#endif

