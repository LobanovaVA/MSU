#include <stdio.h>
#include <stdlib.h>

#include "msr_matr.h"

int
get_off_diag_ind (int nx, int ny, int l, int *J)
{
  int i, j;
  l2ij (nx, ny, i, j, l);
  return get_off_diag_ind (nx, ny, i, j, J);
}

int
get_off_diag_ind (int nx, int ny, int i, int j, int *J)
{
  /* узлы в внутри */
  if (0 < i && i < nx && 0 < j && j < ny)
    {
      ij2l (nx, ny, i + 1, j    , J[0]);
      ij2l (nx, ny, i    , j - 1, J[1]);
      ij2l (nx, ny, i - 1, j - 1, J[2]);
      ij2l (nx, ny, i - 1, j    , J[3]);
      ij2l (nx, ny, i    , j + 1, J[4]);
      ij2l (nx, ny, i + 1, j + 1, J[5]);
      return 6;
    }

  /* узлы на границе - левый */
  if (i == 0  && 0 < j && j < ny)
    {
      ij2l (nx, ny, i + 1, j    , J[0]);
      ij2l (nx, ny, i    , j - 1, J[1]);
      ij2l (nx, ny, i    , j + 1, J[2]);
      ij2l (nx, ny, i + 1, j + 1, J[3]);
      return 4;
    }

  /* узлы на границе - правый */
  if (i == nx && 0 < j && j < ny)
    {
      ij2l (nx, ny, i    , j - 1, J[0]);
      ij2l (nx, ny, i - 1, j - 1, J[1]);
      ij2l (nx, ny, i - 1, j    , J[2]);
      ij2l (nx, ny, i    , j + 1, J[3]);
      return 4;
    }

  /* узлы на границе - нижний */
  if (j == 0  && 0 < i && i < nx)
    {
      ij2l (nx, ny, i + 1, j    , J[0]);
      ij2l (nx, ny, i - 1, j    , J[1]);
      ij2l (nx, ny, i    , j + 1, J[2]);
      ij2l (nx, ny, i + 1, j + 1, J[3]);
      return 4;
    }

  /* узлы на границе - верхний */
  if (j == ny && 0 < i && i < nx)
    {
      ij2l (nx, ny, i + 1, j    , J[0]);
      ij2l (nx, ny, i    , j - 1, J[1]);
      ij2l (nx, ny, i - 1, j - 1, J[2]);
      ij2l (nx, ny, i - 1, j    , J[3]);
      return 4;
    }

  /* узел на углу - 0 0 */
  if (j == 0 && i == 0)
    {
      ij2l (nx, ny, i + 1, j    , J[0]);
      ij2l (nx, ny, i    , j + 1, J[1]);
      ij2l (nx, ny, i + 1, j + 1, J[2]);
      return 3;
    }

  /* узел на углу  - nx ny */
  if (i == nx && j == ny)
    {
      ij2l (nx, ny, i    , j - 1, J[0]);
      ij2l (nx, ny, i - 1, j - 1, J[1]);
      ij2l (nx, ny, i - 1, j    , J[2]);
      return 3;
    }

  /* узел на углу  - 0 ny */
  if (i == 0 && j == ny)
    {
      ij2l (nx, ny, i + 1, j    , J[0]);
      ij2l (nx, ny, i    , j - 1, J[1]);
      return 2;
    }

  /* узел на углу  - nx 0 */
  if (i == nx && j == 0)
    {
      ij2l (nx, ny, i - 1, j    , J[0]);
      ij2l (nx, ny, i    , j + 1, J[1]);
      return 2;
    }

  fprintf (stderr, "FATAL ERROR: get_off_diag_ind\n");
  abort ();
  return -1;
}


int
get_off_diag_ind_elem (int nx, int ny, int l, int *J, double *diag, double *tmp)
{
  int i, j;
  l2ij (nx, ny, i, j, l);
  return get_off_diag_ind_elem (nx, ny, i, j, J, diag, tmp);
}

int
get_off_diag_ind_elem (int nx, int ny, int i, int j, int *J, double *diag, double *tmp)
{
  /* узлы в внутри */
  if (0 < i && i < nx && 0 < j && j < ny)
    {
      ij2l (nx, ny, i + 1, j    , J[0]);
      ij2l (nx, ny, i    , j - 1, J[1]);
      ij2l (nx, ny, i - 1, j - 1, J[2]);
      ij2l (nx, ny, i - 1, j    , J[3]);
      ij2l (nx, ny, i    , j + 1, J[4]);
      ij2l (nx, ny, i + 1, j + 1, J[5]);

      *diag = 0.5;
      for (int j = 0; j < 6; j++)
        tmp[j] = 1. / 12;

      return 6;
    }

  /* узлы на границе - левый */
  if (i == 0  && 0 < j && j < ny)
    {
      ij2l (nx, ny, i + 1, j    , J[0]);
      ij2l (nx, ny, i    , j - 1, J[1]);
      ij2l (nx, ny, i    , j + 1, J[2]);
      ij2l (nx, ny, i + 1, j + 1, J[3]);

      *diag = 0.25;
      tmp [0] = 1. / 12;
      tmp [1] = 1. / 24;
      tmp [2] = 1. / 24;
      tmp [3] = 1. / 12;

      return 4;
    }

  /* узлы на границе - правый */
  if (i == nx && 0 < j && j < ny)
    {
      ij2l (nx, ny, i    , j - 1, J[0]);
      ij2l (nx, ny, i - 1, j - 1, J[1]);
      ij2l (nx, ny, i - 1, j    , J[2]);
      ij2l (nx, ny, i    , j + 1, J[3]);

      *diag = 0.25;
      tmp [0] = 1. / 24;
      tmp [1] = 1. / 12;
      tmp [2] = 1. / 12;
      tmp [3] = 1. / 24;

      return 4;
    }

  /* узлы на границе - нижний */
  if (j == 0  && 0 < i && i < nx)
    {
      ij2l (nx, ny, i + 1, j    , J[0]);
      ij2l (nx, ny, i - 1, j    , J[1]);
      ij2l (nx, ny, i    , j + 1, J[2]);
      ij2l (nx, ny, i + 1, j + 1, J[3]);

      *diag = 0.25;
      tmp [0] = 1. / 24;
      tmp [1] = 1. / 24;
      tmp [2] = 1. / 12;
      tmp [3] = 1. / 12;

      return 4;
    }

  /* узлы на границе - верхний */
  if (j == ny && 0 < i && i < nx)
    {
      ij2l (nx, ny, i + 1, j    , J[0]);
      ij2l (nx, ny, i    , j - 1, J[1]);
      ij2l (nx, ny, i - 1, j - 1, J[2]);
      ij2l (nx, ny, i - 1, j    , J[3]);

      *diag = 0.25;
      tmp [0] = 1. / 24;
      tmp [1] = 1. / 12;
      tmp [2] = 1. / 12;
      tmp [3] = 1. / 24;

      return 4;
    }

  /* узел на углу - 0 0 */
  if (j == 0 && i == 0)
    {
      ij2l (nx, ny, i + 1, j    , J[0]);
      ij2l (nx, ny, i    , j + 1, J[1]);
      ij2l (nx, ny, i + 1, j + 1, J[2]);

      *diag = 1. / 6;
      tmp [0] = 1. / 24;
      tmp [1] = 1. / 24;
      tmp [2] = 1. / 12;

      return 3;
    }

  /* узел на углу  - nx ny */
  if (i == nx && j == ny)
    {
      ij2l (nx, ny, i    , j - 1, J[0]);
      ij2l (nx, ny, i - 1, j - 1, J[1]);
      ij2l (nx, ny, i - 1, j    , J[2]);

      *diag = 1. / 6;
      tmp [0] = 1. / 24;
      tmp [1] = 1. / 12;
      tmp [2] = 1. / 24;

      return 3;
    }

  /* узел на углу  - 0 ny */
  if (i == 0 && j == ny)
    {
      ij2l (nx, ny, i + 1, j    , J[0]);
      ij2l (nx, ny, i    , j - 1, J[1]);

      *diag = 1. / 12;
      tmp [0] = 1. / 24;
      tmp [1] = 1. / 24;

      return 2;
    }

  /* узел на углу  - nx 0 */
  if (i == nx && j == 0)
    {
      ij2l (nx, ny, i - 1, j    , J[0]);
      ij2l (nx, ny, i    , j + 1, J[1]);

      *diag = 1. / 12;
      tmp [0] = 1. / 24;
      tmp [1] = 1. / 24;

      return 2;
    }

  fprintf (stderr, "FATAL ERROR: get_off_diag_ind_elem\n");
  abort ();
  return -1;
}
