#ifndef BLOCK_ACTION_H
#define BLOCK_ACTION_H

#include "addition.h"

void get_full_block (int matrix_size, int block_size, const matr A, matr A_bl, int i_bl, int j_bl, int div, int mod);
void get_diag_block (int matrix_size, int block_size, const matr A, matr A_bl, int i_bl, int div, int mod);
void get_vect_block (int block_size, vect D, const vect D_bl, int i_bl, int div, int mod);
void get_column (int matrix_size, int block_size, matr A, column R_col, int j_bl, int div, int mod);

void put_full_block (int matrix_size, int block_size, matr A, const matr A_bl, int i_bl, int j_bl, int div, int mod);
void put_diag_block (int matrix_size, int block_size, matr A, const matr A_bl, int i_bl, int div, int mod);
void put_vect_block (int block_size, vect D, const vect D_bl, int i_bl, int div, int mod);

#endif

