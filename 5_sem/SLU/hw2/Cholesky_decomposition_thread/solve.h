#ifndef SOLVE_H
#define SOLVE_H

#include "addition.h"
#include "in_out.h"
#include "norm.h"
#include "block_action.h"
#include "matr_operation.h"

/* ============ cholesky ============ */
bool cholesky_symm_storage (int size, matr A, vect D, double norm);
bool cholesky (int size, int shift, matr A, vect D, double norm);

/* ========== thread solve ========== */
void solve_thread (int matrix_size, int block_size, matr A, vect B, vect X, vect D, vect S,
                   int th_p, int th_i, pthread_barrier_t *barrier, int *status);

void cholesky_thread (int matrix_size, int block_size, matr A, vect D, double norm,
                      int th_p, int th_i, pthread_barrier_t *barrier, int *status);

/* ============ calculate block R ============ */
bool calc_diag_block_R (int block_size, vect D, column R_col, matr_bl Ri, vect_bl D_bl,
                        double norm, int i, int div, int mod);

void calc_full_block_R (int matrix_size, int block_size, matr A, vect D,
                        matr_bl Ri_inv, vect_bl D_i, matr_bl R_is, column R_col,
                        matr_bl R_bl, vect_bl D_bl, int i, int s, int div, int mod);

/* ============ thread calculate solution ============ */
void calc_y_thread (int matrix_size, int block_size, matr A, vect B,
                    int th_p, int th_i, pthread_barrier_t *barrier);

void calc_x_thread (int matrix_size, int block_size, matr A, vect B, vect S,
                    int th_p, int th_i, pthread_barrier_t *barrier);

void calc_x_thread2 (int matrix_size, int block_size, matr A, vect B, vect S,
                     int th_p, int th_i, pthread_barrier_t *barrier);

void DB (int matrix_size, int block_size, vect D, vect B,
         int th_p, int th_i, pthread_barrier_t *barrier);

#endif

