#include "window/window.h"
extern bool calculating;
#define MIN_N 1
#define MAX_N 15*1e7

void
Window::change_func ()
{
  if (!calculating)
    {
      change_func_id ();
      change_func_label ();
      drawer->set_func (f);

      if (displayed == Displayed_type::etalon)
        etalon_case ();
      else
        after_slot ();
    }
}

void
Window::change_graph ()
{
  if (!calculating)
    {
      displayed = (Displayed_type) (((int) displayed + 1) % 3);

      switch (displayed)
        {
        case Displayed_type::etalon:
        case Displayed_type::residual:
          drawer->change_displ ();
          break;
        case Displayed_type::approx:
          fl_gui_changed = true;
          if (!calculating)
            after_slot ();
          break;

        }

      change_fmax_label ();
      change_displ_label ();

      drawer->update_surface_coeffs ();
      drawer->updateGL ();
    }
}

void
Window::zoom_in ()
{
  drawer->zoom_in ();
  change_s_label ();
}

void
Window::zoom_out ()
{
  drawer->zoom_out ();
  change_s_label ();
}

void
Window::double_n ()
{
  if (!calculating)
    {
      if (nx * ny < MAX_N)
        {
          window_time = get_time();

          nx *= 2;
          ny *= 2;
          change_nx_ny_label ();

          if (displayed == Displayed_type::etalon)
            etalon_case ();
          else
            after_slot ();
        }
      else
        print_message (Message_type::information, "Autoupdate arguments",
                       "Too big argument for nx/ny.\nValue of nx/ny didn't change.");
    }
}

void
Window::half_n ()
{
  if (!calculating)
    {
      if (nx > MIN_N && ny > MIN_N)
        {
          nx /= 2;
          ny /= 2;
          change_nx_ny_label ();

          if (displayed == Displayed_type::etalon)
            etalon_case ();
          else
            after_slot ();
        }
      else
        print_message (Message_type::information, "Autoupdate arguments",
                       "Too small argument for nx/ny.\nValue of nx/ny didn't change.");
    }
}

void
Window::add_delta ()
{
  drawer->add_delta ();
  change_p_label ();
}

void
Window::subtract_delta ()
{
  drawer->subtract_delta ();
  change_p_label ();
}

void
Window::rot_clock ()
{
  drawer->rot_clock ();
  change_rh_label ();
}

void
Window::rot_unclock ()
{
  drawer->rot_unclock ();
  change_rh_label ();
}

void
Window::rot_up ()
{
  drawer->rot_up ();
  change_rv_label ();
}

void
Window::rot_down ()
{
  drawer->rot_down ();
  change_rv_label ();
}


void
Window::change_func_id ()
{
  func_id = (func_id + 1) % 8;
  f = f_value [func_id];
}

void
Window::etalon_case ()
{
  working_grid.reset (new Grid_info (nx, ny, pol));
  after_calculation ();
}

void
Window::after_slot ()
{
  calculating = true;
  before_calculation ();

  th_out++;
  pthread_cond_broadcast (&cond);
}
