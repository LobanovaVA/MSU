#ifndef MATR_OPERATION_H
#define MATR_OPERATION_H

#include "addition.h"

void A_minus_RtDR (int lim, int size, matr A, matr R1, vect D, matr R2);
void DRtA (int size, vect D, matr R, matr A);

int inverse_upper_matrix (int size, int shift, matr R, matr E, double eps);

void B_minus_RtY (int k_size, int m_size, vect B, matr R, vect Y);
void RtB (int size, vect R, vect B, vect Y);

void RB (int size, vect Ri_inv, vect B_i, vect B);
void B_MX (int size, vect B, matr M, vect X);
#endif

