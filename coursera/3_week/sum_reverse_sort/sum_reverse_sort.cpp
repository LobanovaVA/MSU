#include <algorithm>
#include "sum_reverse_sort.h"

int 
Sum (int x, int y)
{
  return x + y;
}

string 
Reverse (string s)
{
  std::reverse (s.begin (), s.end ());
  return s;
}

void 
Sort (vector<int>& nums)
{
  std::sort (nums.begin (), nums.end ());
}

#ifdef MY
int main ()
{
  return 0;
}
#endif