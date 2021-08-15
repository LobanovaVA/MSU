#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename RandomIt>
void MergeSort (RandomIt range_begin, RandomIt range_end)
{
  int dist = range_end - range_begin;
  if (dist < 2)
    return;

  auto range_middle = range_begin + dist / 2;
  vector<typename RandomIt::value_type> elems_1
    (range_begin, range_middle);
  MergeSort (elems_1.begin (), elems_1.end ());

  vector<typename RandomIt::value_type> elems_2
    (range_middle, range_end);
  MergeSort (elems_2.begin (), elems_2.end ());

  std::merge (elems_1.begin (), elems_1.end (),
              elems_2.begin (), elems_2.end (),
              range_begin);
}

int main () 
{
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
  MergeSort (begin (v), end (v));

  for (int x : v) 
    cout << x << " ";
  cout << endl;

  return 0;
}