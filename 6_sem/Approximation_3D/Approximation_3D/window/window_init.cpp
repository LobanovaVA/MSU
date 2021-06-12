#include "window.h"
#include "msr_matr/msr_matr_ind.h"

Window::Window  (int nx_, int ny_, int f_k, int th_p, double eps_,
                 polygon *pol_, QWidget *parent) : QWidget(parent)
{
  connect (this, SIGNAL (calculation_completed ()), this, SLOT (after_calculation ()));

  init_window (nx_, ny_, f_k, th_p, eps_, pol_);
  init_window_gui ();

  init_thread ();
  start_threads ();
}

Window::~Window ()
{
  pthread_barrier_destroy (&barrier);
}

void
Window::fill_f_arrays ()
{
  def_func def_f;

  f_value[0] = def_f.f_0;
  f_value[1] = def_f.f_1;
  f_value[2] = def_f.f_2;
  f_value[3] = def_f.f_3;
  f_value[4] = def_f.f_4;
  f_value[5] = def_f.f_5;
  f_value[6] = def_f.f_6;
  f_value[7] = def_f.f_7;

  f_names[0] = def_f.f_0_name;
  f_names[1] = def_f.f_1_name;
  f_names[2] = def_f.f_2_name;
  f_names[3] = def_f.f_3_name;
  f_names[4] = def_f.f_4_name;
  f_names[5] = def_f.f_5_name;
  f_names[6] = def_f.f_6_name;
  f_names[7] = def_f.f_7_name;
}

void
Window::init_window (int nx_, int ny_, int f_k, int th_p, double eps_, polygon *pol_)
{
  nx = nx_;
  ny = ny_;
  func_id = f_k;
  threads_num = th_p;
  eps = eps_;
  pol = pol_;

  fill_f_arrays ();
  f = f_value [func_id];

  allocate_memory ();
}

void
Window::allocate_memory ()
{
  data.allocate_memory (get_matrix_len (nx, ny), get_matrix_size (nx, ny), threads_num);
  data.set_zero ();

  working_grid.reset (new Grid_info (nx, ny, pol));
}

void
Window::init_thread ()
{
  if (pthread_barrier_init (&barrier, NULL, threads_num))
    {
      fprintf (stderr, "FATAL ERROR: init_thread\n");
      abort ();
    }

  cond = PTHREAD_COND_INITIALIZER;

  th_info.reset (new thread_info[threads_num]);

  init_th_info ();
}

void
Window::init_th_info ()
{
  for (int k = 0; k < threads_num; k++)
    {
      th_info[k].nx = nx;
      th_info[k].ny = ny;
      th_info[k].eps = eps;

      th_info[k].f = f;
      th_info[k].grid = working_grid.get ();

      th_info[k].th_p = threads_num;
      th_info[k].th_k = k;
      th_info[k].barrier = &barrier;
      th_info[k].cond = &cond;
      th_info[k].proceed = true;
      th_info[k].th_out = &th_out;

      th_info[k].data = &data;
      th_info[k].window = this;
    }

}

void
Window::start_threads ()
{
  pthread_t tid;

  for (int k = 0; k < threads_num; k++)
    {
      if (pthread_create (&tid, 0, pthread_func, th_info.get () + k))
        {
          fprintf (stderr, "FATAL ERROR: create thread #%d\n", k);
          abort ();
        }
    }
}

void
Window::print_debug () const
{
  char msg[LEN];
  sprintf (msg, "f_id = %d nx = %8.d ny = %8.d mode = %d p = %3.1d s = %3.1d maxf = %10.3e", \
           func_id, nx, ny, (int) displayed, drawer->get_p (), drawer->get_s (), drawer->get_fmax ());
  qDebug() << msg;
}
