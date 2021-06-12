#include <stdio.h>
#include <stdlib.h>

#include "msr_matr_ind.h"

void
ij2l (int nx, int /*ny*/, int  i, int  j, int &l)
{
   l = i + j * (nx + 1);
}

void
l2ij (int nx, int /*ny*/, int &i, int &j, int  l)
{
  j = l / (nx + 1);
  i = l - j * (nx + 1);
}

int
get_matrix_len (int nx, int ny)
{
  int diag = get_matrix_size (nx, ny);
  int offdiag = get_off_diag_num (nx, ny);
  return diag + offdiag + 1;
}

int
get_matrix_size (int nx, int ny)
{
  return (nx + 1) * (ny + 1);
}

int
get_off_diag_max (int /*nx*/, int /*ny*/)
{
  return 6;
}

int
get_off_diag_num (int nx, int ny)
{
//  int sum = 0;
//  for (int i = 0; i <= nx; i++)
//    for (int j = 0; j <= ny; j++)
//        sum += get_off_diag_num (nx, ny, i, j);
//  return sum;
  return 6 * (nx - 1) * (ny - 1) + 8 * (nx - 1) + 8 * (ny - 1) + 10;
}

int
get_off_diag_num (int nx, int ny, int l)
{
  int i, j;
  l2ij (nx, ny, i, j, l);
  return get_off_diag_num (nx, ny, i, j);
}


int
get_off_diag_num (int nx, int ny, int i, int j)
{
  /* узлы в внутри */
  if (0 < i && i < nx && 0 < j && j < ny)
    return 6;

  /* узлы на границе */
  if (   (i == 0  && 0 < j && j < ny) /* левый */
      || (i == nx && 0 < j && j < ny) /* правый */
      || (j == 0  && 0 < i && i < nx) /* нижний */
      || (j == ny && 0 < i && i < nx) /* верхний */ )
    return 4;

   /* узлы в углах */
  if ((i == 0 && j == 0 ) || (i == nx && j == ny))
    return 3;

  if ((i == 0 && j == ny) || (i == nx && j == 0 ))
    return 2;

  fprintf (stderr, "FATAL ERROR IN get_off_diag_num %d %d %d %d\n", nx, ny, i, j);
  abort ();
  return -1;
}
