#ifndef MATR_OPERATION_H
#define MATR_OPERATION_H

#include "addition.h"
#include "in_out.h"

void A_minus_RtDR_no_unroll (int size, matr A, matr R1, vect D, matr R2);
void A_minus_RtDR (int size, matr A, matr R1, vect D, matr R2);

void DRtA (int size, vect D, matr R, matr A);

bool inverse_upper_matrix  (int size, int shift, matr R, matr E, double norm);

void Bs_MtB (int size, vect B_s, matr M, vect B);
void RtB (int size, vect Ri_inv, vect B_diff, vect B);

void Bdiff_MB (int size, vect B_diff, matr M, vect B);
void Bdiff_total (int size, int th_p, vect B_diff, vect S);
void RB (int size, vect Ri_inv, vect B_i, vect B);

#endif

