#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

// Реализуйте здесь
// * класс Matrix
// * оператор ввода для класса Matrix из потока istream
// * оператор вывода класса Matrix в поток ostream
// * оператор проверки на равенство двух объектов класса Matrix
// * оператор сложения двух объектов класса Matrix

class Matrix
{
  int m_rows = 0;
  int m_cols = 0;
  vector<int> matr;

  int ij2l (int i, int j) const { return i * m_cols + j; }
  bool check_corr_ind (int ind) const { return 0 <= ind && ind < m_rows * m_cols; }
  bool check_corr_ind (int i, int j) const
  { return 0 <= i && i < m_rows && 0 <= j && j < m_cols; }

public:
  Matrix () = default;
  Matrix (int num_rows, int num_cols) { Reset (num_rows, num_cols); }

  ~Matrix () = default;

  void
  Reset (int num_rows, int num_cols)
  {
    if (num_rows < 0 || num_cols < 0)
      throw std::out_of_range ("negative size");

    if (num_rows == 0 || num_cols == 0)
      num_rows = num_cols = 0;

    m_rows = num_rows;
    m_cols = num_cols;
    matr.assign (num_rows * num_cols, 0);
  }

  int
  At (int row, int col) const
  {
    if (check_corr_ind (row, col))
      return matr.at (ij2l (row, col));
    else
      throw std::out_of_range ("out of size");
  }

  int&
  At (int row, int col)
  {
    if (check_corr_ind (row, col))
      return matr.at (ij2l (row, col));
    else
      throw std::out_of_range ("out of size");
  }

  int GetNumRows ()    const { return m_rows; }
  int GetNumColumns () const { return m_cols; }

  bool is_empty () const { return (m_cols == 0 || m_rows == 0); }

};


istream&
operator>> (istream &in, Matrix &M)
{
  int num_rows, num_cols;
  in >> num_rows >> num_cols;
  M.Reset (num_rows, num_cols);

  for (int row = 0; row < M.GetNumRows (); row++)
    for (int col = 0; col < M.GetNumColumns (); col++)
      in >> M.At (row, col);

  return in;
}

ostream&
operator<< (ostream &out, const Matrix &M)
{
  out << M.GetNumRows () << " " << M.GetNumColumns () << endl;
  for (int row = 0; row < M.GetNumRows (); row++)
    {
      for (int col = 0; col < M.GetNumColumns (); col++)
        out << M.At (row, col) << " ";
      out << endl;
    }
  return out;
}

bool
operator== (const Matrix &M1, const Matrix &M2)
{
  if (M1.GetNumRows () == M2.GetNumRows () && M1.GetNumColumns () == M2.GetNumColumns ())
    {
      for (int row = 0; row < M1.GetNumRows (); row++)
        for (int col = 0; col < M1.GetNumColumns (); col++)
          if (M1.At (row, col) != M2.At (row, col))
            return false;

      return true;
    }
  else
    return false;
}

Matrix
operator+ (const Matrix &M1, const Matrix &M2)
{
  if (M1.GetNumRows () != M2.GetNumRows () || M1.GetNumColumns () != M2.GetNumColumns ())
    throw std::invalid_argument ("incorr sum");

  Matrix M (M1.GetNumRows (), M1.GetNumColumns ());

  for (int row = 0; row < M.GetNumRows (); row++)
    for (int col = 0; col < M.GetNumColumns (); col++)
      M.At (row, col) = M1.At (row, col) + M2.At (row, col);

  return M;
}

int main() {
  Matrix one;
  Matrix two;

  cin >> one >> two;
  cout << one + two << endl;

  return 0;
}
