#ifndef MSR_MATR_IND_H
#define MSR_MATR_IND_H

#include <stdio.h>

static inline void
get_ind_thread (int n, int p, int k, int &i1, int &i2)
{
  i1 = n * k;
  i1 /= p;
  i2 = n * (k + 1);
  i2 /= p;

  //fprintf (stderr, "n = %d p = %d k = %d i1 = %d i2 = %d \n", n, p, k, i1, i2);
}

// === msr_matr_pattern === //
void ij2l (int nx, int ny, int  i, int  j, int &l);
void l2ij (int nx, int ny, int &i, int &j, int  l);

int get_matrix_len  (int nx, int ny);
int get_matrix_size (int nx, int ny);

int get_off_diag_max (int nx, int ny);
int get_off_diag_num (int nx, int ny);
int get_off_diag_num (int nx, int ny, int l);
int get_off_diag_num (int nx, int ny, int i, int j);

#endif // MSR_MATR_IND_H
