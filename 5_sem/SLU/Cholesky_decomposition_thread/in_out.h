#ifndef IN_OUT_H
#define IN_OUT_H

#include "addition.h"

/* ========== initialization ========== */
double f (int s, int n, int i, int j);

int read_matrix (const char *file_name, int matrix_size, matr matrix);

void init_matrix (const int mode, int matrix_size, matr matrix);
void init_vector_B (int matrix_size, matr matrix, vect vector_B);


/* ========== thread initialization ========== */
void init_zero_thread (int matrix_size, int block_size, matr A, vect B, vect X, vect D, vect S,
                       int th_p, int th_i, pthread_barrier_t *barrier, int *status);

void init_thread (int matrix_size, int block_size, const int mode, char *filename,
                  matr A, vect B, int th_p, int th_i, pthread_barrier_t *barrier, int * status);

void init_matrix_thread (const int mode, int matrix_size, int block_size, matr matrix,
                         int th_p, int th_i, pthread_barrier_t *barrier);

void read_matrix_thread (const char *filename, int matrix_size, matr matrix,
                         int th_i, pthread_barrier_t *barrier, int *status);

void init_vector_B_thread (int matrix_size, matr matrix, vect vector_B,
                           int th_i, pthread_barrier_t *barrier);


/* ========== print ========== */
void print_matrix (double *data, int line_size, int column_size, int print_size);
void print_symmetric_matrix (matr matrix, int matrix_size, int print_size);
void print_upper_matrix (matr matrix, int matrix_size, int print_size);


/* ========== thread print ========== */
void print_after_init_thread (matr matrix, vect vector_B, int matrix_size,
                              int print_size, int th_i, pthread_barrier_t *barrier);

void print_after_solve_thread (vect vector_X, int matrix_size, int print_size,
                               int th_i, pthread_barrier_t *barrier);

void print_time_thread (int th_i, double time_thread, double time_total,
                        pthread_barrier_t *barrier);
#endif

