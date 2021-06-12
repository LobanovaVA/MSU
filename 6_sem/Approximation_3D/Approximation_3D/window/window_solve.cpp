#include "window/window.h"
#include "msr_matr/msr_matr_ind.h"

extern bool calculating;

void
Window::signal_calculation_completed ()
{
  emit calculation_completed ();
}

void
Window::before_calculation ()
{
  allocate_memory ();
  init_th_info ();
}

void
Window::after_calculation ()
{
  window_time = (get_time () - window_time);
  calculating = false;

  if (fl_gui_changed)
    {
      fl_gui_changed = false;
      drawer->change_displ ();
    }

  drawer->update_surface (working_grid);
  drawer->set_approx (answer);
  drawer->update_surface_coeffs ();

  change_fmax_label ();
  drawer->updateGL();
}

void
Window::set_answer (double *result)
{
  int size = get_matrix_size (nx, ny);
  answer.resize (size);

  for (int i = 0; i < size; i++)
    answer[i] = result[i];
}

