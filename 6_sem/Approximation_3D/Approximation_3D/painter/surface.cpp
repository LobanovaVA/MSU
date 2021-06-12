#include "surface.h"
#include "msr_matr/msr_matr_ind.h"

Surface::Surface(Grid_info *grid_, func f_)
{
  grid = grid_;
  f = f_;

  fill_etalon ();
  f_coeffs = etalon;
  find_minmax ();
}

double
Surface::get_fmax () const
{
  return std::max (fabs (f_minmax.min), fabs (f_minmax.max));
}


// === change params === //
void
Surface::change_displ ()
{
  displayed = (Displayed_type) (((int) displayed + 1) % 3);

  switch (displayed)
    {
    case Displayed_type::etalon:
      fill_etalon ();
      f_coeffs = etalon;
      break;
    case Displayed_type::approx:
      f_coeffs = approx;
      break;
    case Displayed_type::residual:
      fill_etalon ();
      fill_residual ();
      break;
    }

  find_minmax ();
}

void
Surface::change_p (int n)
{
  if (n == 0)
    p++;
  else
    p--;
}


// === update data === //
void
Surface::update_coeffs ()
{
  update_f_coeffs ();

  int nx, ny;
  grid->get_nx_ny (nx, ny);

  int l;
  ij2l (nx, ny, nx / 2, ny / 2, l);
  f_coeffs[l] += 0.1 * p * get_fmax ();

  find_minmax ();
}

void
Surface::update_f_coeffs ()
{
  switch (displayed)
    {
    case Displayed_type::etalon:
      fill_etalon ();
      f_coeffs = etalon;
      break;
    case Displayed_type::approx:
      f_coeffs = approx;
      break;
    case Displayed_type::residual:
      fill_etalon ();
      fill_residual ();
      break;
    }
}

void
Surface::update (Grid_info  *grid_)
{
  grid = grid_;

  int nx, ny;
  grid->get_nx_ny (nx, ny);

  f_coeffs.resize (get_matrix_size (nx, ny));
}

void
Surface::update (std::unique_ptr<Grid_info> &grid_ptr_)
{
  grid_ptr.swap (grid_ptr_);
  grid = grid_ptr.get ();

  int nx, ny;
  grid->get_nx_ny (nx, ny);
  f_coeffs.resize (get_matrix_size (nx, ny));
}


// === fill vectors === //
void
Surface::fill_etalon ()
{
  int nx, ny, i, j;
  grid->get_nx_ny (nx, ny);

  int size = get_matrix_size (nx, ny);
  etalon.resize (size);

  for (int l = 0; l < size; l++)
    {
      l2ij(nx, ny, i, j, l);
      etalon[l] = grid->get_f_value_ij (f, i, j);
    }
}

void
Surface::fill_residual ()
{
  int size = etalon.size ();
  for (int i = 0; i < size; i++)
      f_coeffs[i] = fabs (etalon[i] - approx[i]);
}

void
Surface::find_minmax ()
{
  auto [min_iter, max_iter] = std::minmax_element (begin (f_coeffs), end (f_coeffs));

  f_minmax.max = *max_iter;
  f_minmax.min = *min_iter;
}
