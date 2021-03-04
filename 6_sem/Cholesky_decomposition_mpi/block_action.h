#ifndef BLOCK_ACTION_H
#define BLOCK_ACTION_H

#include "addition.h"

void MPI_action_elem_row (int ind, size_arguments &size_args, matr *ptr_columns,
                          vect buff_row, action_type action);

void get_full_block (int i_bl, int s_bl, size_arguments &size_args, matr *ptr_columns, matr_bl R_bl);
void get_diag_block (int i_bl, size_arguments &size_args, matr *ptr_columns, matr_bl R_bl);
void get_column (int j_bl, size_arguments &size_args, matr *ptr_columns, column_bl R_col);

void put_full_block (int i_bl, int s_bl, size_arguments &size_args, matr *ptr_columns, matr_bl R_bl);
void put_diag_block (int ind_bl, size_arguments &size_args, matr *ptr_columns, matr_bl R_i);

#endif

