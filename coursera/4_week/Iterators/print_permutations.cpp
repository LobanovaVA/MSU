#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

template <typename T>
ostream& operator<< (ostream & out, const vector<T> & v)
{
  for (const auto& it : v)
    out << it << ' ';
  out << endl;
  return out;
}

int main () 
{
  int N;
  cin >> N;
  
  vector<int> v (N);
  std::iota (v.rbegin (), v.rend (), 1);

  cout << v;
  while (prev_permutation (v.begin (), v.end ()))
    cout << v;

  return 0;
}
