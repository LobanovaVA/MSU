#ifndef CHOL_EIGENVAL_H
#define CHOL_EIGENVAL_H

#include "addition.h"

int transform_symm_matrix (int size, matr A, double norm);

int find_eigenvalues (int size, matr A, vect V, double eps, double norm);
void find_eigenval_2dimsymm_matr (int size, matr A);

int cholesky_decomp_tridiag_matr (matr A, int dim, double norm, int size);
int cholesky_decomp_tridiag_matr (matr V, int dim, double norm);

void cacl_product (matr A, int dim, int size);
void cacl_product (matr V, int dim);

void make_shift (int size, matr A, int dim, double shift_v);
void make_shift (int size, matr A, int dim, double shift_v, vect V, int fl = 1);

#endif

