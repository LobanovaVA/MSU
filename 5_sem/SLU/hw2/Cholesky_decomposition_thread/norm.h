#ifndef NORM_H
#define NORM_H

#include "addition.h"

double norm_A (int size, matr A);
double norm_Ax_b (int size, matr A, vect B, vect X);
double norm_x_x0 (int matrix_size, vect X);

void norm_Ax_b_thread (int size, matr A, vect B, vect X, int th_p, int th_i,
                       pthread_barrier_t *barrier, double &residual);
#endif

