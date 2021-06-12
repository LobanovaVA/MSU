#include "window.h"

void
Window::paintEvent (QPaintEvent * /* event */)
{
  m = width ();
  h = height () - DEFAULT_INFO_H;

  QPen pen (Qt::red);
  QPainter painter (this);
  painter.fillRect (5, 5, m, h, QBrush (QColor (48, 10, 36)));

  init_draw_point_etalon ();
  auto [min_y_etalon, max_y_etalon] = (this)->get_min_max ();


  // === cubic spline method === //
  init_start_approx_data (*(this->approx_spline));
  calc_approx_out (*(this->approx_spline), fl_recalc);

  if (displayed_graph == Displayed_type::both_error)
    calc_diff (*(this->approx_spline));

  auto [min_y_spline, max_y_spline] = approx_spline->get_min_max ();
  auto [min_y, max_y] = (this)->get_displayed_min_max (min_y_etalon, max_y_etalon, min_y_spline, max_y_spline);


  // === shift newton method === //
  if (n <= 50 && displayed_graph != Displayed_type::cubic_spline)
    {
      init_start_approx_data (*(this->approx_newton));
      calc_approx_out (*(this->approx_newton), fl_recalc);

      if (displayed_graph == Displayed_type::both_error)
        calc_diff (*(this->approx_newton));

      auto [min_y_newton, max_y_newton] = approx_newton->get_min_max ();

      min_y = std::min (min_y, min_y_newton);
      max_y = std::max (max_y, max_y_newton);
    }

  fl_recalc = 0;


  // ===== paint action ===== //
  painter.save ();
  make_coordinate_transform (painter, max_y, min_y);

  if (displayed_graph != Displayed_type::shift_newton)
    {
      pen.setColor (QColor (255, 7, 140));
      paint_graph (approx_spline->in, approx_spline->out, painter, pen);
    }

  if (n <= 50 && displayed_graph != Displayed_type::cubic_spline)
    {
      pen.setColor (QColor (7, 255, 140));
      paint_graph (approx_newton->in, approx_newton->out, painter, pen);
    }

  if (displayed_graph != Displayed_type::both_error)
    {
      pen.setColor (Qt::white);
      beauty_dash_pen (pen);
      paint_graph (draw_x_etalon, draw_fx_etalon, painter, pen);
    }
#ifdef TODO
  что делать с возмущением при рисовании ??
#endif

  paint_axis (painter);
  painter.restore ();

  paint_info (painter, min_y, max_y);

#ifdef FIX
  if (n > 50 && displayed_graph != Displayed_type::cubic_spline)
    print_message (Message_type::information, "Approximation",
    "For n > 50 polynomial interpolation isn't built.");
#endif
}

void
Window::make_coordinate_transform (QPainter &painter, double max_y, double min_y)
{
#ifdef TODO
  рассмотреть случаи маленьких min/max
    #endif

  //printf("\n k = %d min=%10.3e max=%10.3e\n", func_id, min_y, max_y);

  painter.translate (0, h);
  painter.scale (1, -1);

  if (std::abs (max_y - min_y) < EPS)
    {
      dr_max = max_y + 0.5 * std::abs (max_y);
      dr_min = min_y - 0.5 * std::abs (min_y);

      if (! (max_y < 0 || max_y > 0))
       {
          dr_max = 1;
          dr_min = -1;
        }
    }
  else
    {
      double delta_y = 0.01 * (max_y - min_y);
      dr_max = max_y + delta_y;
      dr_min  = min_y - delta_y;
    }

  //printf("draw   min=%10.3e max=%10.3e\n", dr_min, dr_max);
}

void
Window::paint_graph (std::vector<double> &x, std::vector<double> &fx, QPainter &painter, QPen &pen)
{
  int len = x.size ();
  painter.setPen (pen);

  QPainterPath p (QPointF (0, draw_y(fx[0])));

  for (int i = 1; i < len; i++)
    p.lineTo (QPointF (i, draw_y(fx[i])));

  painter.drawPath (p);
}

void
Window::paint_axis (QPainter &painter)
{
  QPen pen (QColor (190, 180, 120), 0, Qt::DotLine);
  painter.setPen (pen);

  if (a < 0 && b > 0) /* Oy */
    painter.drawLine (QPointF (draw_x (0), 0), QPointF (draw_x (0), h));

  if (dr_min < 0 && dr_max > 0) /* Ox */
    painter.drawLine (QPointF (0, draw_y (0)), QPointF (width(), draw_y (0)));
}

void
Window::paint_info (QPainter &painter, double min_y, double max_y)
{

  int place = height() - DEFAULT_INFO_H;
  char buf[LEN];

  sprintf (buf, "[ a ; b ] = [ %10.3e ; %10.3e ]", a, b);
  QString ab = buf;

  sprintf (buf, "[ F_min ; F_max ]  = [ %10.3e ; %10.3e ]", min_y,  max_y);
  QString min_max = buf;

  sprintf (buf, "width = %d height = %d", m,  h);
  QString wh = buf;

  QString func_name = "k = " + QString::number (func_id) + ":  " + f_name;
  QString args = "n = " + QString::number (n) + "  p = " + QString::number (p) + "  s = " + QString::number (s);

  QString graph_name;
  switch (displayed_graph)
    {
    case Displayed_type::shift_newton:
      graph_name = "shift newton";
      break;
    case Displayed_type::cubic_spline:
      graph_name = "cubic spline";
      break;
    case Displayed_type::both_methods:
      graph_name = "both methods";
      break;
    case Displayed_type::both_error:
      graph_name = "both errors";
      break;
    }


  QPen pen (Qt::black, 1, Qt::SolidLine);
  pen.setCosmetic (1);
  painter.setPen (pen);
  painter.setFont (QFont("Arial", 5));

  painter.drawText (10, place + 20, func_name);
  painter.drawText (10, place + 40, args);
  painter.drawText (10, place + 60, ab);
  painter.drawText (10, place + 80, min_max);
  painter.drawText (10, place + 100, wh);
  painter.drawText (10, place + 120, "displayed type = " + graph_name);


  painter.setBackgroundMode (Qt::OpaqueMode);
  QBrush brush (Qt::white, Qt::BrushStyle::SolidPattern);

  painter.setBackground (brush);
  painter.drawText (10, place + 140, "etalon");

  brush.setColor (QColor (7, 255, 140));
  painter.setBackground (brush);
  painter.drawText (60, place + 140, " shift newton");

  brush.setColor (QColor (255, 7, 140));
  painter.setBackground (brush);
  painter.drawText (160, place + 140, " cubic spline");

  print_debag ();
}


void
Window::beauty_dash_pen (QPen &pen)
{
  QVector<qreal> dashes;
  qreal space = 8;
  dashes << 8 << space;
  pen.setDashPattern(dashes);
}

int
Window::draw_x (double t)
{
  return (int) ((t - a) * m / (b - a));
}

#include <QDebug>
int
Window::draw_y (double t)
{
  return (int) ((t - dr_min) * h / (dr_max - dr_min));
}

