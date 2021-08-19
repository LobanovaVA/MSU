#include <iostream>
#include <iomanip>  
#include <vector>
#include <string>
#include <memory>
#include <cmath>

using namespace std;

constexpr double PI = 3.14;

class Figure
{
public:
  virtual string Name ()      const = 0;
  virtual double Area ()      const = 0;
  virtual double Perimeter () const = 0;

  virtual ~Figure () = default;
};


class Triangle : public Figure
{
private:
  const int a;
  const int b;
  const int c;

public:
  Triangle (const int a_, const int b_, const int c_)
    : a (a_), b (b_), c (c_) {}

  string Name () const override { return "TRIANGLE"; }
  double Area () const override 
  {
    double p = (a + b + c) / 2.;
    return sqrt (p * (p - a) * (p - b) * (p - c));
  }
  double Perimeter () const override { return a + b + c; }
};

class Rect : public Figure
{
private:
  const int a;
  const int b;

public:
  Rect (const int a_, const int b_) : a (a_), b (b_) {}

  string Name () const override { return "RECT"; };
  double Area () const override { return a * b; }
  double Perimeter () const override { return 2 * (a + b); }
};

class Circle : public Figure
{
private:
  const int a;

public:
  Circle (const int a_) : a (a_) {}

  string Name () const override { return "CIRCLE"; };
  double Area () const override { return PI * a * a; }
  double Perimeter () const override { return 2 * PI * a; }
};


shared_ptr<Figure> CreateFigure (istream& is)
{
  shared_ptr<Figure> ans;
  string type;
  int a, b, c;

  is >> type;

  if (type == "TRIANGLE")
  {
    is >> a >> b >> c;
    ans = make_shared<Triangle> (a, b, c);
  }
  else if (type == "RECT")
  {
    is >> a >> b;
    ans = make_shared<Rect> (a, b);
  }
  else if (type == "CIRCLE")
  {
    is >> a;
    ans = make_shared<Circle> (a);
  }
  else
    cout << "Unknown figure type" << endl;

  return ans;
}

int main () 
{
  vector<shared_ptr<Figure>> figures;
  for (string line; getline (cin, line); ) 
  {
    istringstream is (line);

    string command;
    is >> command;
    if (command == "ADD") 
    {
      // Пропускаем "лишние" ведущие пробелы.
      is >> std::ws;
      figures.push_back (CreateFigure (is));
    } 
    else if (command == "PRINT") 
    {
      for (const auto& current_figure : figures) 
      {
        cout << fixed << setprecision (3)
             << current_figure->Name () << " "
             << current_figure->Perimeter () << " "
             << current_figure->Area () << endl;
      }
    }
  }
  return 0;
}