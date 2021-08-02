#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

#ifded COURSERA
template <typename T>
vector<T> FindGreaterElements (const set<T> & elements, const T & border)
{
  auto it = find_if (elements.begin (), elements.end (), 
    [border] (const T& elem) { return elem > border; });

  return {it, end(elements)};
}
#endif

template <typename T>
vector<T> FindGreaterElements (const set<T> & elements, const T & border)
{
  vector<T> ans;

  auto l = [border] (const T& elem) { return elem > border; };

  auto it = find_if (elements.begin (), elements.end (), l);

  while (it != elements.end ())
  {
    ans.push_back (*it);
    it = find_if (++it, elements.end (), l);
  }

  std::sort (ans.begin (), ans.end ());
  return ans;
}

int main () 
{
  for (int x : FindGreaterElements (set<int>{1, 5, 7, 8}, 5))
    cout << x << " ";
  cout << endl;
  
  string to_find = "Python";
  cout << FindGreaterElements (set<string>{"C", "C++"}, to_find).size () << endl;
  return 0;
}
