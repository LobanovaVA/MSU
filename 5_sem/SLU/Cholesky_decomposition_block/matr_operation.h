#ifndef MATR_OPERATION_H
#define MATR_OPERATION_H

#include "addition.h"
#include "in_out.h"

void A_minus_RtDR_no_unroll (int size, matr A, matr R1, vect D, matr R2);
void A_minus_RtDR (int size, matr A, matr R1, vect D, matr R2);

void DRtA (int size, vect D, matr R, matr A);

bool inverse_upper_matrix  (int size, matr R, matr E, double norm);

#endif

