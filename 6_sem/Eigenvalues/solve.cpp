#include "solve.h"
#include "residual.h"

#include "in_out.h"

int
find_eigenvalues (int size, matr A, vect V, double eps)
{
  int iter = 0, ind, dim, ret;
  double norm, eps_lim, shift_v;

  norm = norm_tridiag_matr (size, A);
  printf("\nMatrix norm = %.3e\n", norm);
  eps_lim = norm * eps;

  for (dim = size, ind = size - 1; dim > 2; dim--, ind--)
    {
      while (fabs (A[get_IND (ind, ind - 1, size)]) > eps_lim)
        {
          (void) shift_v;
          //          shift_v = A[get_IND (ind, ind, size)];
          //          make_shift (size, A, dim, shift_v, norm);

          ret = cholesky_decomp_tridiag_matr (size, A, dim, norm);
          if (ret != SUCCESS)
            return ret;

          cacl_product (size, A, dim);
          //          ret = make_shift (size, A, dim, -shift_v, norm);
          iter++;
        }
    }

  if (size > 1)
    find_eigenval_2dimsymm_matr (size, A);

  for (ind = 0; ind < size; ind++)
    V[ind] = A[get_IND (ind, ind, size)];

  return iter;
}


int
cholesky_decomp_tridiag_matr (int size, matr A, int dim, double norm)
{
  int i;
  double l_ii, elem;

  for (i = 0; i < dim; i++)
    {
      elem = (i > 0) ?  A[get_IND(i - 1, i, size)] : 0;
      elem *= elem;
      l_ii = A[get_IND (i, i, size)] - elem;

      if (is_small (l_ii, norm * EPS))
        return ERROR_SINGULAR_MATRIX;

      if (l_ii < 0)
        {
          printf ("\nERROR: L_{%d, %d} = %.3e\n", i, i, l_ii);
          return ERROR_NEGATIVE_MATRIX;
        }

      l_ii = sqrt (l_ii);
      A[get_IND (i, i, size)] = l_ii;

      if (i < dim - 1)
        A[get_IND (i, i + 1, size)] /= l_ii;
    }

  return SUCCESS;
}


void
cacl_product (int size, matr A, int dim)
{
  int i = 0;
  double elem, l_ii = A[0];

  while (i < dim - 1)
    {
      /* A_{i,i} = L_{i,i}^2 + L_{i+1,i+1}^2
       * A_{i,i+1} = L_{i,i+1} * L_{i+1,i+1} */

      elem = A[get_IND (i, i + 1, size)];
      A[get_IND (i, i, size)] = l_ii * l_ii + elem * elem;

      i++;
      l_ii = A[get_IND (i, i, size)];
      A[get_IND (i - 1, i, size)] = elem * l_ii;
    }

  A[get_IND (dim - 1, dim - 1, size)] = l_ii * l_ii;
}


void
find_eigenval_2dimsymm_matr (int size, matr A)
{
  /* | a b |  y^2 - (c + a)y + (ac - b^2) = 0
   * | b c |  y^2 - ty + s = 0 y = 0.5 (t +- discr)   */

  double t, s, discr;

  if (is_small (A[1], EPS))
    return;

  t = A[0] + A[get_IND (1, 1, size)];
  s = A[0] * A[get_IND (1, 1, size)] - A[1] * A[1];
  discr = sqrt (t * t - 4 * s);

  A[0] = 0.5 * (t + discr);
  A[get_IND (1, 1, size)] = 0.5 * (t - discr);
}


void
make_shift (int size, matr A, int dim, double shift_v)
{
  for (int i = 0; i < dim; i++)
    A[get_IND (i, i, size)] -= shift_v;
}



/* ============ matrix transformation ============ */
int
transform_symm_matrix (int size, matr A)
{
  int h, s, c;
  double norm, vect_len_sqauared = 0, vect_len, next_elem_norm;
  double cos_v, sin_v, x_i, x_j, b_ii, b_ij, b_ji, b_jj;
  double *ptr_A_hh;

  norm = norm_symm_matr (size, A);
  printf("\nMatrix norm = %.3e\n", norm);

  for (h = 0; h < size - 2; h++)
    {
      /* transform h-th column=string  */
      ptr_A_hh = A + get_IND (h, h, size);
      /* start from next elem after A_{hh} */
      vect_len_sqauared = ptr_A_hh [1] * ptr_A_hh [1];

      /* transform A_{h + 2, step}..A_{size - 1, s} */
      for (s = 2; s < size - h; s++)
        {
          next_elem_norm = ptr_A_hh[s] * ptr_A_hh[s];
          vect_len_sqauared += next_elem_norm;
          vect_len = sqrt (vect_len_sqauared);

          if (next_elem_norm < EPS * norm || vect_len < EPS * norm)
            {
              ptr_A_hh[s] = 0;
              continue;
            }

          /* calc T_{h + 1, h + s} */
          cos_v = ptr_A_hh[1] / vect_len;
          sin_v = - ptr_A_hh[s] / vect_len;
          ptr_A_hh[1] = vect_len;
          ptr_A_hh[s] = 0;

          /* B' = T_{h + 1, h + s} * (c-th column) */
          x_i = A[get_IND (h + 1, h + 1, size)];
          x_j = A[get_IND (h + s, h + 1, size)];
          b_ii = x_i * cos_v - x_j * sin_v;
          b_ji = x_i * sin_v + x_j * cos_v;

          x_i = A[get_IND (h + 1, h + s, size)];
          x_j = A[get_IND (h + s, h + s, size)];
          b_ij = x_i * cos_v - x_j * sin_v;
          b_jj = x_i * sin_v + x_j * cos_v;

          for (c = h + 2; c < size; c++)
            {
              if (c != h + s)
                {
                  x_i = A[get_IND (h + 1, c, size)];
                  x_j = A[get_IND (h + s, c, size)];

                  A[get_IND (h + 1, c, size)] = x_i * cos_v - x_j * sin_v;
                  A[get_IND (h + s, c, size)] = x_i * sin_v + x_j * cos_v;
                }
            }

          /* B = b' * T_{h + 1, h + s} */
          A[get_IND (h + 1, h + 1, size)] = b_ii * cos_v - b_ij * sin_v;
          //A[get_IND (h + s, h + 1, size)] = b_ji * cos_v - b_jj * sin_v;
          A[get_IND (h + 1, h + s, size)] = b_ii * sin_v + b_ij * cos_v;
          A[get_IND (h + s, h + s, size)] = b_ji * sin_v + b_jj * cos_v;
        }

      if (is_small (ptr_A_hh [0], EPS * norm))
        return ERROR_EPS;
    }

  if (is_small (A[get_IND (size - 1, size - 1, size)], EPS * norm))
    return ERROR_EPS;

  return SUCCESS;
}
