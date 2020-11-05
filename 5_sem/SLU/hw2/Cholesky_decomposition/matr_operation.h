#ifndef MATR_OPERATION_H
#define MATR_OPERATION_H

#include "addition.h"
#include "in_out.h"

void A_minus_RtDR (int size, matr A, matr R1, vect D, matr R2);
bool reverse_upper_matrix  (int size, matr R, matr E, double norm);
void DRtA (int size, vect D, matr R, matr A);

#endif

