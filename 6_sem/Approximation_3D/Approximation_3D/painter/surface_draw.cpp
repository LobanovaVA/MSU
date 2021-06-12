#include "surface.h"
#include "addition.h"
#include "msr_matr/msr_matr_ind.h"

void
Surface::draw ()
{
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

  max_z = std::max (fabs (f_minmax.max), fabs (f_minmax.min));

  if (is_small (max_z, EPS))
    max_z = EPS;

  draw_all_triangle ();
}

void
Surface::draw_shadow ()
{
  point_2d A, B, C, D;
  grid->fill_shadow_points (A, B, C, D);

  glBegin (GL_POLYGON);
  {
    glVertex3d (A.x, A.y, 0.);
    glVertex3d (B.x, B.y, 0.);
    glVertex3d (C.x, C.y, 0.);
    glVertex3d (D.x, D.y, 0.);
  }
  glEnd();
}

void
Surface::draw_all_triangle ()
{
  /* A --- B        P3   P2---P3
   * |     |         |   |
   * D --- C   P1---P2   P1      */

  point_2d A, B, C, D;
  grid->fill_shadow_points (A, B, C, D);

  int n = PAINT_SIZE;
  double sh_x = grid->get_width () / n,
         sh_y = grid->get_height() / n;

  point_2d P1, P2, P3;
  for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        {
          P1.x = D.x + i * sh_x;
          P1.y = D.y + j * sh_y;

          P3.x = P1.x + sh_x;
          P3.y = P1.y + sh_y;

          P2.x = P1.x + sh_x;
          P2.y = P1.y;
          draw_triangle (P1, P2, P3);

          P2.x = P1.x;
          P2.y = P1.y + sh_y;
          draw_triangle (P1, P2, P3);
        }
}


void
Surface::draw_triangle (point_2d &P1, point_2d &P2, point_2d &P3)
{

  double f_T1 = grid->get_f_value_P (f_coeffs, P1);
  double f_T2 = grid->get_f_value_P (f_coeffs, P2);
  double f_T3 = grid->get_f_value_P (f_coeffs, P3);

  glBegin(GL_TRIANGLES);
  {
      glVertex3d (P1.x, P1.y, f_T1 / max_z);
      glVertex3d (P2.x, P2.y, f_T2 / max_z);
      glVertex3d (P3.x, P3.y, f_T3 / max_z);
  }
  glEnd();
}
