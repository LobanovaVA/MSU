#ifndef RESIDUAL_H
#define RESIDUAL_H

#include "addition.h"

void cacl_inv_symm_matr (int size, matr A, double &track, double &lenght);
void cacl_inv_tridiag_matr (int size, matr A, double &track, double &lenght);
void cacl_inv_diag_matr (int size, vect V, double &track, double &lenght);

double norm_symm_matr (int size, matr A);
double norm_tridiag_matr (int size, matr A);

#endif

