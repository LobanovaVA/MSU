#ifndef SOLVE_H
#define SOLVE_H

#include "addition.h"

int MPI_solve (size_arguments &size_args, matr *ptr_columns, vect D, vect B, vect Y);

int MPI_cholesky (size_arguments &size_args, matr *ptr_columns, vect D, buff_ptr diag_inv, double eps);
int cholesky (int size, int shift, matr A, vect D, double eps);

int calc_diag_block_R (int ind_bl, size_arguments &size_args, vect D, column_bl R_col, double eps);
void calc_full_block_R (int i_bl, int s_bl, size_arguments &size_args,  matr *ptr_columns, vect D,
                        column_bl R_col_i, matr_bl Ri_inv, matr_bl R_is_buf, matr_bl R_js_buf);

void MPI_calc_y (size_arguments &size_args, matr *ptr_columns, vect B, vect Y, buff_ptr diag_inv);
void MPI_calc_x (size_arguments &size_args, matr *ptr_columns, vect B, vect X);

void DB (int size, vect D, vect B);

#endif

