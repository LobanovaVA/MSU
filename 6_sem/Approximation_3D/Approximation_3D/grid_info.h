#ifndef GRID_INFO_H
#define GRID_INFO_H

#include "addition.h"
#include "struct.h"

class Grid_info
{
private:
  int nx = 1;
  int ny = 1;
  polygon *pol = nullptr;

public:
  Grid_info (int nx_, int ny_, polygon *p_);

  void get_nx_ny (int &nx_, int &ny_) const;
  double get_width () const;
  double get_height () const;
  polygon* get_polygon () const;

  void get_middle (point_2d &p) const;
  double get_f_value_ij (func &f, const int i, const int j) const;
  double get_f_value_ij (func &f, const int i, const int j, const int nx_, const int ny_) const;
  void fill_shadow_points (point_2d &A, point_2d &B, point_2d &C, point_2d &D) const;

  double get_f_value_P (std::vector <double> &f_coeffs, const point_2d &P) const;

private:
  void find_index (const point_2d &P, int &i, int &j) const;
  void fill_point_ij (point_2d &p, const int i, const int j) const;
  void fill_point_ij (point_2d &p, const int i, const int j, const int nx_, const int ny_) const;
  void fill_triangles (triangle &T1, triangle &T2, const int i, const int j) const;
  triangle which_triangle (const point_2d &P, triangle &T1, triangle &T2) const;
  double which_side (const point_2d &a, const point_2d &b, const point_2d &c) const;
  bool is_in_triangle (const point_2d &P, triangle &T) const;
  double interpolate (std::vector<double> &f, const point_2d &P, const triangle &T) const;

};

#endif // GRID_INFO_H
