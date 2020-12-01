#ifndef SOLVE_H
#define SOLVE_H

#include "addition.h"
#include "in_out.h"
#include "norm.h"
#include "block_action.h"
#include "matr_operation.h"

int solve (int matrix_size, int block_size, matr A, vect B, vect D,
           vect X, matr R1, matr R2, matr Ri, matr A_bl, vect D_bl);

bool cholesky_symm_storage (int size, matr A, vect D, double norm);
bool cholesky (int size, int shift, matr A, vect D, double norm);

bool cholesky_block (int matrix_size, int block_size, matr A, vect D,
                     matr R1, matr R2, matr Ri, matr A_bl, vect D_bl, double norm);

bool calc_diag_block_R (int matrix_size, int block_size, matr A, vect D, matr R1, matr Ri,
                        matr A_bl, vect D_bl, double norm, int i, int div, int mod);
bool calc_full_block_R (int matrix_size, int block_size, matr A, vect D, matr R1, matr R2,
                        matr Ri, matr A_bl, vect D_bl, int i, int s, int div, int mod);

void calc_y_not_block (int matrix_size, matr A, vect B);
void calc_x_not_block (int matrix_size, matr A, vect D, vect B);

#endif

