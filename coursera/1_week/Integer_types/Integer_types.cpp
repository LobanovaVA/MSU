#include <iostream>
#include <vector>
#include <limits>
using namespace std;

int main_v1 () 
{
  cout << " === v1 === " << endl;

  cout << "sizeof (int16_t) = " << sizeof (int16_t) << endl;

  cout << "sizeof (int) = " << sizeof (int) << endl;
  cout << "min of int = " << numeric_limits<int>::min () << endl;
  cout << "max of int = " << numeric_limits<int>::max () << endl;

  cout << "sizeof (long int) = " << sizeof (long int) << endl;
  cout << "min of long int = " << numeric_limits<long int>::min () << endl;
  cout << "max of long int = " << numeric_limits<long int>::max () << endl;

  cout << endl;
  return 0;
}


int main_v2 () 
{
  cout << " === v2 === " << endl;

  cout << "sizeof (int) = " << sizeof (int) << endl;
  cout << "min of int = " << numeric_limits<int>::min () << endl;
  cout << "max of int = " << numeric_limits<int>::max () << endl;


  cout << endl;
  cout << "min of int - 1 = " << numeric_limits<int>::min () - 1 << endl;
  cout << "max of int + 1 = " << numeric_limits<int>::max () + 1 << endl;

  int x = -2'000'000'000;
  unsigned  y = x;
  cout << x << ' ' << y << endl;
  cout << endl;

  x = -1;
  y = 1;
  cout << "x < y: " << (x < y) << endl;

  cout << endl;
  return 0;
}


int main_v3 () 
{
  cout << " === v3 === " << endl;

  vector<int> x = {4, 5};

  cout << "1st way: " << endl;
  for (size_t i = 0 ; i < x.size (); i++)
    cout << " i = " << i << " x[i] = " << x[i] <<  endl;

  cout << "2nd way: " << endl;
  for (int i = 0 ; i < static_cast<int> (x.size ()); i++)
    cout << " i = " << i << " x[i] = " << x[i] <<  endl;

  cout << endl;
  

  cout << "All without last elem: " << endl;
  for (size_t i = 0 ; i + 1 < x.size (); i++)
    cout << " i = " << i << " x[i] = " << x[i] <<  endl;

  vector<int> v;
  cout << "Empty vector: " << endl;
  for (size_t i = 0 ; i + 1 < v.size (); i++)
    cout << " i = " << i << " v[i] = " << v[i] <<  endl;

  cout << endl;
  return 0;
}

int main ()
{
  main_v1 ();
  main_v2 ();
  main_v3 ();
  return 0;
}