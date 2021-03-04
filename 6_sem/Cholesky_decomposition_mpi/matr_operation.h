#ifndef MATR_OPERATION_H
#define MATR_OPERATION_H

#include "addition.h"

void A_minus_RtDR (int size, matr A, matr R1, vect D, matr R2);
void DRtA (int size, vect D, matr R, matr A);

int inverse_upper_matrix (int size, int shift, matr R, matr E, double eps);

#endif

