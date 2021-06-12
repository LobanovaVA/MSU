#ifndef MSR_MATR_PATTERN_H
#define MSR_MATR_PATTERN_H

#include <sys/sysinfo.h>
#include <pthread.h>

#define MAX_IT 1000
#include "msr_matr_ind.h"

typedef double (*func) (double, double);

// === masr_matr_pattern === //
int get_off_diag_ind (int nx, int ny, int l, int *J);
int get_off_diag_ind (int nx, int ny, int i, int j, int *J);

int get_off_diag_ind_elem (int nx, int ny, int l, int *J, double *diag, double *tmp);
int get_off_diag_ind_elem (int nx, int ny, int i, int j, int *J, double *diag, double *tmp);


// === msr_matr_fill === //
void fill_I_diag (int nx, int ny, int *I);
void fill_A_full (int nx, int ny, double *A, int *I, int p, int k);

//void fill_I_full (int nx, int ny, int *I, int p, int k);
//void fill_A_scl (int nx, int ny, double *A, int *I, int p, int k);

//inline double get_scalar_phi_l  (int nx, int ny, int l);
//inline double get_scalar_phi_lr (int nx, int ny, int l, int r);


// === msr_matr_operation === //
void matr_mult_vector (int matrix_size, double *A, int *I, double *x,
                       double *y, int p, int k, pthread_barrier_t *barrier);

void apply_precond_Jacobi (int matrix_size, double *A, int *I, double *r,
                           double *v, int p, int k, pthread_barrier_t *barrier);

void lin_comb_vector (int size, double *x, double *y, double t,
                      int p, int k, pthread_barrier_t *barrier);

double scalar_prod (int size, double *x, double *y, double *buf,
                    int p, int k, pthread_barrier_t *barrier);


// === msr_matr_solve === //
int min_residual_solve (double *A, int *I, int matrix_size, double *b, double *x, double *r, double *u, double *v,
                        double *buf, double eps, int maxit, int p, int k, pthread_barrier_t *barrier);

void min_residual_solve_full (double *A, int *I, int matrix_size, double *b, double *x, double *r, double *u, double *v,
                              double *buf, double eps, int maxit, int p, int k, pthread_barrier_t *barrier);

#endif // MSR_MATR_PATTERN_H
