#include "grid_info.h"
#include "msr_matr/msr_matr_ind.h"


Grid_info::Grid_info (int nx_, int ny_, polygon *p_)
{
  nx = nx_;
  ny = ny_;
  pol = p_;
}

void
Grid_info::get_nx_ny (int &nx_, int &ny_) const
{
  nx_ = nx;
  ny_ = ny;
}

double
Grid_info::get_width () const
{
  return pol->DR.x - pol->UL.x;
}

double
Grid_info::get_height () const
{
  return pol->UL.y - pol->DR.y;
}

polygon*
Grid_info::get_polygon () const
{
  return pol;
}

void
Grid_info::get_middle (point_2d &p) const
{
  p.x = get_width () / 2;
  p.y = get_height () / 2;
}

double
Grid_info::get_f_value_ij (func &f, const int i, const int j) const
{
  point_2d curr;
  fill_point_ij (curr, i, j);
  return f (curr.x, curr.y);
}

double
Grid_info::get_f_value_ij (func &f, const int i, const int j, const int nx_, const int ny_) const
{
  point_2d curr;
  fill_point_ij (curr, i, j, nx_, ny_);

  //fprintf(stderr, "nx = %d i = %d j = %d  (%10.3e, %10.3e) f = %10.3e\n", nx_, i, j, curr.x, curr.y, f (curr.x, curr.y));
  return f (curr.x, curr.y);
}


void
Grid_info::fill_point_ij (point_2d &p, const int i, const int j) const
{
  p.x = pol->UL.x + i * get_width ()  / nx;
  p.y = pol->DR.y + j * get_height () / ny;
}

void
Grid_info::fill_point_ij (point_2d &p, const int i, const int j, const int nx_, const int ny_) const
{
  p.x = pol->UL.x + i * get_width ()  / nx_;
  p.y = pol->DR.y + j * get_height () / ny_;
}

void
Grid_info::fill_shadow_points (point_2d &A, point_2d &B,
                               point_2d &C, point_2d &D) const
{
  /* A --- B
   * |     |
   * D --- C */
  A = pol->UL;
  B = point_2d (pol->DR.x, pol->UL.y);
  C = pol->DR;
  D = point_2d (pol->UL.x, pol->DR.y);
}


// === get f value from grid === //
double
Grid_info::get_f_value_P (std::vector <double> &f_coeffs,
                          const point_2d &P) const
{
  int i, j, l;
  find_index (P, i, j);
//  fprintf(stderr, "i = %d j = %d\n", i, j);

  if (i == nx && j == ny)
    {
      ij2l (nx, ny, i, j, l);
      return f_coeffs[l];
    }

  triangle T1, T2;
  fill_triangles (T1, T2, i, j);

  triangle T = which_triangle (P, T1, T2);
  return interpolate (f_coeffs, P, T);
}

void /* T fell into rectangle of calc triangulation with DL point with ind = (i; j) */
Grid_info::find_index (const point_2d &P, int &i, int &j) const
{
  i = (int) ((P.x - pol->UL.x) * nx / get_width ());
  j = (int) ((P.y - pol->DR.y) * ny / get_height ());

  if (i > nx || j > ny)
    {
      fprintf (stderr, "FATAL ERROR: find_index\n");
      abort ();
    }
}

void /* DL point with ind = (i; j) is vertex of 2 triangles of calc triangulation */
Grid_info::fill_triangles (triangle &T1, triangle &T2, const int i, const int j) const
{
  /* rigth border:
   * SINGULAR T2:  b -X- c  (i,j+1) -X- ..
   *               |           |
   *               a         (i,j)           */
  if (i == nx)
    {
      T2.singular = true;
      T2.border = true;

      int l_a, l_b;
      ij2l (nx, ny, i, j    , l_a);
      ij2l (nx, ny, i, j + 1, l_b);

      T2.a.second = l_a;
      T2.b.second = l_b;

      fill_point_ij (T2.a.first, i, j    );
      fill_point_ij (T2.b.first, i, j + 1);

      return;
    }

  /* upper border:
   * SINGULAR T1:        c    ...
   *                     X     X
   *               a --- b   (i,j) --- (i+1,j)  */
  if (j == ny)
    {
      T1.singular = true;
      T1.border = true;

      int l_a, l_b;
      ij2l (nx, ny, i    , j, l_a);
      ij2l (nx, ny, i + 1, j, l_b);

      T1.a.second = l_a;
      T1.b.second = l_b;

      fill_point_ij (T1.a.first, i    , j);
      fill_point_ij (T1.b.first, i + 1, j);

      return;
    }

  /* full triangle :
   * T1:     c            (i+1,j+1)   T2: b---c   (i,j+1) --- (i+1,j+1)
   *         |                |           |          |
   *     a---b   (i,j) --- (i+1,j)        a        (i,j)                 */

  /* fill index */
  int l_a, l_b1, l_b2, l_c;
  ij2l (nx, ny, i    , j    , l_a);
  ij2l (nx, ny, i + 1, j    , l_b1);
  ij2l (nx, ny, i    , j + 1, l_b2);
  ij2l (nx, ny, i + 1, j + 1, l_c);

  T1.a.second = T2.a.second = l_a;
  T1.c.second = T2.c.second = l_c;

  T1.b.second = l_b1;
  T2.b.second = l_b2;

  /* fill coordinate */
  fill_point_ij (T1.a.first, i    , j    );
  fill_point_ij (T1.c.first, i + 1, j + 1);

  fill_point_ij (T1.b.first, i + 1, j    );
  fill_point_ij (T2.b.first, i    , j + 1);

  T2.a.first = T1.a.first;
  T2.c.first = T1.c.first;
}

triangle
Grid_info::which_triangle (const point_2d &P, triangle &T1, triangle &T2) const
{
  if (T1.singular)
    return T1;

  if (T2.singular)
    return T2;

  if (is_in_triangle (P, T1))
    return T1;

  if (is_in_triangle (P, T2))
    return T2;

  fprintf (stderr, "FATAL ERROR: which_triangle\n");
  abort ();
}

double
Grid_info::which_side (const point_2d &a, const point_2d &b, const point_2d &c) const
{
    return (a.x - c.x) * (b.y - c.y) -
           (b.x - c.x) * (a.y - c.y);
}

bool
Grid_info::is_in_triangle (const point_2d &P, triangle &T) const
{
    double d_AB = which_side (P, T.a.first, T.b.first);
    double d_BC = which_side (P, T.b.first, T.c.first);
    double d_AC = which_side (P, T.c.first, T.a.first);

    if (is_small (d_AB, EPS))
      {
        T.border = true;
        return true;
      }

    if (is_small (d_BC, EPS) || is_small (d_AC, EPS))
      return true;

    bool neg = (d_AB < 0) || (d_BC < 0) || (d_AC < 0);
    bool pos = (d_AB > 0) || (d_BC > 0) || (d_AC > 0);

    return !(neg && pos);
}

double
Grid_info::interpolate (std::vector<double> &f, const point_2d &P, const triangle &T) const
{
  if (T.border)
    {
      /* P on leg of triangle:
       *  A (X0, y0) --- P (XP, y0) --- B (X1, y0)
       * f(P) = f(a) + (f(b) - f(a)) * (XP - X0) / (X1 - X0)
       *
       * A (x0, Y0) --- P (x0, YP) --- B (x0, Y1)
       * f(P) = f(a) + (f(b) - f(a)) * (YP - Y0) / (Y1 - Y0)  */

      double len_aP = sqrt (
            (P.x - T.a.first.x) * (P.x - T.a.first.x) +
            (P.y - T.a.first.y) * (P.y - T.a.first.y) );

      double len_AB = sqrt (
            (T.a.first.x - T.b.first.x) * (T.a.first.x - T.b.first.x) +
            (T.a.first.y - T.b.first.y) * (T.a.first.y - T.b.first.y) );

      return f[T.a.second] + (f[T.b.second] - f[T.a.second]) * len_aP / len_AB;
    }

  /* P on inside of trianfle:
   *    xA yA 1       alf       fA                      alf
   * ( xB yB 1 ) * ( bet ) = ( fB )   fP = (x, y, 1) * ( bet )
   *   xC yC 1       gam       fC                      gam
   *
   *  N * C = F  => fP = (x, y, 1) * C = [ (x, y, 1) * N^-1 ] * F = (c1, c2, c3) * F
   *
   *  (x, y, 1) * N^-1 = (c1, c2, c3) => (x, y, 1) = (c1, c2, c3) * N
   *
   *   xA xB xC       c1       x
   * ( yA yB yC ) * ( c2 ) = ( y )
   *   1   1  1       c3       1
   *
   * by Cramer's rule :
   *   c1 = D1 / D               x xB xC
   *   c2 = D2 / D    D1 = det ( y yB yC ) = (x - xB) * (yB - yC) + (y - yB) * (xC - xB)
   *   c3 = D3 / D               1  1  1
   */

  double xA = T.a.first.x, yA = T.a.first.y,
         xB = T.b.first.x, yB = T.b.first.y,
         xC = T.c.first.x, yC = T.c.first.y;
  double xP = P.x, yP = P.y;

  auto D1 = [&] (double x, double y)
  { return (x - xB) * (yB - yC) + (y - yB) * (xC - xB); };

  auto D2 = [&] (double x, double y)
  { return (x - xA) * (yC - yA) + (y - yA) * (xA - xC); };

  auto D3 = [&] (double x, double y)
  { return (x - xA) * (yA - yB) + (y - yA) * (xB - xA); };

  double c1 = D1 (xP, yP) / D1 (xA, yA);
  double c2 = D2 (xP, yP) / D2 (xB, yB);
  double c3 = D3 (xP, yP) / D3 (xC, yC);

  return c1 * f[T.a.second] + c2 * f[T.b.second] + c3 * f[T.c.second];
}



