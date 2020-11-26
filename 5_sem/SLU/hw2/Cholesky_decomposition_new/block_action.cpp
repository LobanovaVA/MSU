#include "block_action.h"

// ====== get block ======
void
get_full_block (int matrix_size, int block_size, const matr A, matr A_bl, int i_bl, int j_bl, int div, int mod)
{
  int i, j, string_lim, column_lim, shift_string, shift_column;

  if (i_bl == div || j_bl == div)
    bzero (A_bl, block_size * block_size * sizeof (double));

  string_lim = (i_bl < div) ? block_size : mod;
  column_lim = (j_bl < div) ? block_size : mod;

  shift_string = i_bl * block_size;
  shift_column = j_bl * block_size;

  for (i = 0; i < string_lim; i++)
    {
      for (j = 0; j < column_lim; j++)
        {
          A_bl[i * block_size + j] = A[get_IND (i + shift_string , j + shift_column, matrix_size)];
        }
    }
}

void
get_diag_block (int matrix_size, int block_size, const matr A, matr A_bl, int i_bl, int div, int mod)
{
  int i, j, size_lim, shift;

  if (i_bl == div)
    bzero (A_bl, block_size * block_size * sizeof (double));

  size_lim = (i_bl < div) ? block_size : mod;
  shift = i_bl * block_size;

  for (i = 0; i < size_lim; i++)
    {
      for (j = i; j < size_lim; j++)
        {
          A_bl[i * block_size + j] = A[get_IND (i + shift, j + shift, matrix_size)];
        }
    }
}

void
get_vect_block (int block_size, const vect D, vect D_bl, int i_bl, int div, int mod)
{
  int i, size_lim, shift;
  //bzero (D_bl, block_size * sizeof (double));

  size_lim = (i_bl < div) ? block_size : mod;
  shift = i_bl * block_size;

  for (i = 0; i < size_lim ; i++)
    {
      D_bl[i] = D[shift + i];
    }
}



// ====== put block ======
void
put_full_block (int matrix_size, int block_size, matr A, const matr A_bl, int i_bl, int j_bl, int div, int mod)
{
  int i, j, string_lim, column_lim, shift_string, shift_column;

  string_lim = (i_bl < div) ? block_size : mod;
  column_lim = (j_bl < div) ? block_size : mod;

  shift_string = i_bl * block_size;
  shift_column = j_bl * block_size;

  for (i = 0; i < string_lim; i++)
    {
      for (j = 0; j < column_lim; j++)
        {
          A[get_IND (i + shift_string , j + shift_column, matrix_size)] = A_bl[i * block_size + j];
        }
    }
}

void
put_diag_block (int matrix_size, int block_size, matr A, const matr A_bl, int i_bl, int div, int mod)
{
  int i, j, size_lim, shift;

  size_lim = (i_bl < div) ? block_size : mod;
  shift = i_bl * block_size;

  for (i = 0; i < size_lim; i++)
    {
      for (j = i; j < size_lim; j++)
        {
          A[get_IND (i + shift, j + shift, matrix_size)] = A_bl[i * block_size + j];
        }
    }
}


void
put_vect_block (int block_size, vect D, const vect D_bl, int i_bl, int div, int mod)
{
  int i, size_lim, shift;

  size_lim = (i_bl < div) ? block_size : mod;
  shift = i_bl * block_size;

  for (i = 0; i < size_lim ; i++)
    {
      D[shift + i] = D_bl[i];
    }
}

