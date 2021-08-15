#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename RandomIt>
void MergeSort (RandomIt range_begin, RandomIt range_end)
{
  int dist = range_end - range_begin;
  if (dist < 3)
    return;

  auto range_1_part = range_begin;
  auto range_2_part = range_1_part + dist / 3;
  auto range_3_part = range_2_part + dist / 3;

  vector<typename RandomIt::value_type> elems_1
    (range_1_part, range_2_part);
  MergeSort (elems_1.begin (), elems_1.end ());

  vector<typename RandomIt::value_type> elems_2
    (range_2_part, range_3_part);
  MergeSort (elems_2.begin (), elems_2.end ());

  vector<typename RandomIt::value_type> elems_3
    (range_3_part, range_end);
  MergeSort (elems_3.begin (), elems_3.end ());

  vector<typename RandomIt::value_type> buffer;
  std::merge (elems_1.begin (), elems_1.end (),
              elems_2.begin (), elems_2.end (),
              std::back_inserter (buffer));

  std::merge ( buffer.begin (),  buffer.end (),
              elems_3.begin (), elems_3.end (),
              range_begin);
}

int main () 
{
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
  MergeSort (begin (v), end (v));

  for (int x : v) 
    cout << x << " ";
  cout << endl;

  return 0;
}