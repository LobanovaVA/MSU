#include "window.h"
#include "def_func.h"

void
Window::set_recalc ()
{
  fl_recalc = 1;
  update ();
}

void
Window::set_func ()
{
  def_func func;
  switch (func_id)
    {
    case 0:
      func.set_f0 (this);
      break;
    case 1:
      func.set_f1 (this);
      break;
    case 2:
      func.set_f2 (this);
      break;
    case 3:
      func.set_f3 (this);
      break;
    case 4:
      func.set_f4 (this);
      break;
    case 5:
      func.set_f5 (this);
      break;
    case 6:
      func.set_f6 (this);
      break;
    }

  set_recalc ();
}

void
Window::change_func ()
{
  func_id = (func_id + 1) % 7;
  set_func();
}

void
Window::change_graph ()
{
  displayed_graph = (Displayed_type) (((int) displayed_graph + 1) % 4);
  update ();
}


int
Window::zoom (double coef)
{
  double midpoint = (a + b) / 2;
  double length = b - midpoint;
  length *= coef;

  if (2 * length < MIN_DIST)
    {
      print_message (Message_type::information,
                     "Autoupdate arguments", "Too small istance between a, b.\nDon't zoom.");
      return -1;
    }
  a = midpoint - length;
  b = midpoint + length;
  return 0;
}

void
Window::zoom_in ()
{
  if (!zoom (0.5))
    {
      s++;
      set_recalc ();
    }
}

void
Window::zoom_out ()
{
  if (func_id == 5 && std::max (std::abs (a), std::abs (b)) > EXP_LIM)
    {
      print_message (Message_type::information, "Autoupdate arguments",
                     "Big arguments for exp.\nUsed max [%d; %d].\nReset:\n  a = %4.d\n  b = %4.d",
                     -EXP_LIM, EXP_LIM, DEFAULT_A, DEFAULT_B);
      a = DEFAULT_A;
      b = DEFAULT_B;
    }
  else
    {
      zoom (2);
      s--;
    }

  set_recalc ();
}


void
Window::set_big_n ()
{
  n = 30000000;
  set_recalc ();
}

void
Window::double_n ()
{
  if (n < 15000001)
    {
      n *= 2;
      set_recalc ();
    }
  else
    {
      char msg[LEN] = "Too big argument for n.\nDo you want reset n to max value = 3e7?";
      qDebug() << msg;
      QMessageBox::StandardButton reply
          = QMessageBox::question (0, "Autoupdate arguments", msg, QMessageBox::Yes | QMessageBox::No);

      if (reply == QMessageBox::Yes)
        {
          print_message (Message_type::information, "Autoupdate arguments", "Reset n to max value = 3e7.");
          set_big_n ();
        }
      else
        print_message (Message_type::information, "Autoupdate arguments", "Value of n didn't change.");
    }
}

void
Window::half_n ()
{
  if (n > 2 * SHIFT - 1)
    {
      n /= 2;
      set_recalc ();
    }
  else
    print_message (Message_type::information, "Autoupdate arguments",
                     "Too small argument for n.\nValue of n didn't change.");
}

void
Window::add_delta ()
{
  p++;
  set_recalc ();
}

void
Window::subtract_delta ()
{
  p--;
  set_recalc ();
}


void
Window::set_n_10 ()
{
  n = 10000000;
  set_recalc ();
}


void
Window::set_n_input ()
{
  bool ok;
  int new_n = QInputDialog::getInt
      (this, "Update argument", "Set value for n:",
       DEFAULT_N, SHIFT, 30000000, 1, &ok);

  if (ok)
    {
      n = new_n;
      set_recalc ();
    }
}

void
Window::set_a_input ()
{
  bool ok;
  double new_a = QInputDialog::getDouble
      (this, "Update argument", "Set value for a:",
       b - 1.e-6, -MAX_DIST, b - MIN_DIST, 6, &ok);

  if (ok)
    {
      a = new_a;
      set_recalc ();
    }
}

void
Window::set_b_input ()
{
  bool ok;
  double new_b = QInputDialog::getDouble
      (this, "Update argument", "Set value forb:",
       a + 1.e-6, a + MIN_DIST, MAX_DIST, 6, &ok);

  if (ok)
    {
      b = new_b;
      set_recalc ();
    }
}

void
Window::set_k_input ()
{
  bool ok;
  int new_k = QInputDialog::getInt
      (this, "Update argument", "Set value for k:",
       DEFAULT_N, 0, 6, 1, &ok);

  if (ok)
    {
      func_id = new_k;
      set_func ();
    }
}
