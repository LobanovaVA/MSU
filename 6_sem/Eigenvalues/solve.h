#ifndef CHOL_EIGENVAL_H
#define CHOL_EIGENVAL_H

#include "addition.h"

int transform_symm_matrix (int size, matr A, double norm);

int find_eigenvalues (int size, int fl, matr A, vect V, double eps, double norm);

int cholesky_decomp_tridiag_matr (int size, matr A, int dim, double norm);
void cacl_product (int size, matr A, int dim);

void find_eigenval_2dimsymm_matr (int size, matr A);
void make_shift (int size, matr A, int dim, double shift_v);

#endif

