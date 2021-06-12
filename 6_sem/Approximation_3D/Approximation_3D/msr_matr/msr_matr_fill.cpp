#include "addition.h"
#include "msr_matr/msr_matr.h"
#include "threads/thread_info.h"

void
fill_I_diag (int nx, int ny, int *I)
{
  int matrix_size = get_matrix_size (nx, ny);
  int l, str_size, str_pos = matrix_size + 1;

  for (l = 0; l < matrix_size; l++)
    {
      str_size = get_off_diag_num (nx, ny, l);
      I[l] = str_pos;
      str_pos += str_size;
    }
  I[l] = str_pos;

  if (str_pos != get_matrix_len (nx, ny))
    {
      fprintf (stderr, "FATAL ERROR: fill_I\n");
      abort ();
    }
}

void
fill_A_full (int nx, int ny, double *A, int *I, int p, int k)
{
  int matrix_size = get_matrix_size (nx, ny);

  int l1, l2, sum = 0;
  get_ind_thread (matrix_size, p, k, l1, l2);

  for (int l = l1; l < l2; l++)
    sum += get_off_diag_ind_elem (nx, ny, l, I + I[l], A + l, A + I[l]);


  reduce_sum (p, &sum, 1);
  if (sum + get_matrix_size (nx, ny) + 1 != get_matrix_len (nx, ny))
    {
      fprintf (stderr, "FATAL ERROR: fill_A\n");
      abort ();
    }
}


#if 0 // === WILL BE DELETED === //
void
fill_I_full (int nx, int ny, int *I, int p, int k)
{
  int matrix_size = get_matrix_size (nx, ny);
  int l, str_size, str_pos = matrix_size + 1;

  if (k == MAIN_TREAD)
    {
      for (l = 0; l < matrix_size; l++)
      {
        str_size = get_off_diag_num (nx, ny, l);
        I[l] = str_pos;
        str_pos += str_size;
      }
      I[l] = str_pos;

      if (str_pos != get_matrix_len (nx, ny))
        {
          fprintf (stderr, "FATAL ERROR: fill_I\n");
          abort ();
        }
    }

  int l1, l2;
  int J[6];

  get_ind_thread (matrix_size, p, k, l1, l2);

  for (l = l1; l < l2; l++)
    {
      str_size = get_off_diag_ind (nx, ny, l, J);
      int *I_tmp = I + I[l];
      for (int r = 0; r < str_size; r++)
        I_tmp[r] = J[r];
    }
}
void
fill_A_scl (int nx, int ny, double *A, int *I, int p, int k)
{
  int matrix_size = get_matrix_size (nx, ny);
  int J[6];

  int l1, l2;
  get_ind_thread (matrix_size, p, k, l1, l2);

  for (int l = l1; l < l2; l++)
    {
      A[l] = get_scalar_phi_l (nx, ny, l);
      int str_size = get_off_diag_ind (nx, ny, l, J);
      int pos = I[l];

      for (int r = 0; r < str_size; r++)
        A[pos + r] = get_scalar_phi_lr (nx, ny, l, J[r]);
    }
}


inline double
get_scalar_phi_l (int nx, int ny, int l)
{
  double value = (1. / nx) * (1. / ny);
  int point_type = get_off_diag_num (nx, ny, l);

  switch (point_type)
    {
      case 2: return value / 12;
      case 3: return value / 6;
      case 4: return value / 4;
      case 6: return value / 2;
      default: break;
    }

  fprintf (stderr, "FATAL ERROR IN get_scalar_phi_l\n");
  abort ();
  return -1;
}

inline double
get_scalar_phi_lr (int nx, int ny, int l, int r)
{
  double value = (1. / nx) * (1. / ny);
  int point_type = get_off_diag_num (nx, ny, l);

  int Li, Lj, Ri, Rj;

  switch (point_type)
    {
      case 2: return value / 24;
      case 3:
      {
        l2ij (nx, ny, Li, Lj, l);
        l2ij (nx, ny, Ri, Rj, r);
        if (Li != Ri && Lj != Rj)
          return value / 12;
        else
          return value / 24;
      }

      case 4:
      {
        l2ij (nx, ny, Li, Lj, l);
        l2ij (nx, ny, Ri, Rj, r);
        if (Lj == Rj)
          return value / 24;
        else
          return value / 12;
      }

      case 6: return value / 12;
      default: break;
    }

  fprintf (stderr, "FATAL ERROR IN get_scalar_phi_lr\n");
  abort ();
  return -1;
}
#endif
