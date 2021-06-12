#include "window/window.h"

#ifdef TODO
красиво расположить
#endif
void
Window::init_label_layouts ()
{
  QVBoxLayout *v_layout = new QVBoxLayout (this);

  QHBoxLayout *labels_layout = new QHBoxLayout (this);
  QVBoxLayout *labels_layout_1 = new QVBoxLayout (this);
  QVBoxLayout *labels_layout_2 = new QVBoxLayout (this);
  QVBoxLayout *drawer_layout = new QVBoxLayout (this);

  drawer_layout->addWidget (drawer);

  labels_layout->setAlignment (Qt::AlignLeft);

  labels_layout_1->addWidget (nx_ny_label);
  labels_layout_1->addWidget (func_label);
  labels_layout_1->addWidget (fmax_label);
  labels_layout_1->addWidget (displ_label);

  labels_layout_2->addWidget (s_label);
  labels_layout_2->addWidget (p_label);
  labels_layout_2->addWidget (rh_label);
  labels_layout_2->addWidget (rv_label);

  labels_layout->addLayout (labels_layout_1);
  labels_layout->addLayout (labels_layout_2);

  v_layout->addLayout (labels_layout);
  v_layout->addLayout (drawer_layout);

  v_layout->setStretchFactor (labels_layout, 0);
  v_layout->setStretchFactor (drawer_layout, 1);
}

void
Window::change_label ()
{
  QFont font = QFont("Arial", 5);

  nx_ny_label = new QLabel (this);
  nx_ny_label->setFont (font);
  change_nx_ny_label ();

  displ_label = new QLabel (this);
  displ_label->setFont (font);
  change_displ_label ();

  func_label = new QLabel (this);
  func_label->setFont (font);
  change_func_label ();

  fmax_label = new QLabel (this);
  fmax_label->setFont (font);
  change_fmax_label ();

  s_label = new QLabel (this);
  s_label->setFont (font);
  change_s_label ();

  p_label = new QLabel (this);
  p_label->setFont (font);
  change_p_label ();

  rh_label = new QLabel (this);
  rh_label->setFont (font);
  change_rh_label ();

  rv_label = new QLabel (this);
  rv_label->setFont (font);
  change_rv_label ();
}

void
Window::change_nx_ny_label ()
{
  QString text = "nx = " + QString::number (nx) + " ny = " + QString::number (ny);
  nx_ny_label->setText (text);
  //print_debug ();
}

void
Window::change_displ_label ()
{
  QString text = "displayed type: ";

  switch (displayed)
    {
    case Displayed_type::etalon:
      text += "Etalon";
      break;
    case Displayed_type::approx:
      text += "Approximation";
      break;
    case Displayed_type::residual:
      text += "Residual";
      break;
    }

  displ_label->setText (text);
  //print_debug ();
}

void
Window::change_func_label ()
{
  QString text = "k = " + QString::number (func_id) + ":  f (x) = " + f_names[func_id].c_str();
  func_label->setText (text);
  //print_debug ();
}

void
Window::change_fmax_label ()
{
  char text[LEN];
  sprintf (text, "max abs f = %10.3e", drawer->get_fmax ());
  fmax_label->setText (text);
  print_debug ();
}

void
Window::change_s_label ()
{
  QString text = "scale = " + QString::number (drawer->get_s ());
  s_label->setText (text);
  print_debug ();
}

void
Window::change_p_label ()
{
  QString text = "perturbation = " + QString::number (drawer->get_p ());
  p_label->setText (text);
  print_debug ();
}

void
Window::change_rh_label ()
{
  QString text = "rotate horizontal = " + QString::number (drawer->get_rh ());
  rh_label->setText (text);
}

void
Window::change_rv_label ()
{
  QString text = "rotate vertical = " + QString::number (drawer->get_rv ());
  rv_label->setText (text);
}
