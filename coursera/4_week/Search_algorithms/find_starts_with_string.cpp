#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#ifdef COURSERA
template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
  RandomIt range_begin, RandomIt range_end, string prefix) {
  
  // Все строки, начинающиеся с prefix, больше или равны строке "<prefix>"
  auto left = lower_bound(range_begin, range_end, prefix);
  
  // Составим строку, которая в рамках буквенных строк является
  // точной верхней гранью множества строк, начинающихся с prefix
  string upper_bound = prefix;
  ++upper_bound[upper_bound.size() - 1];
  
  // Первое встреченное слово, не меньшее upper_bound,
  // обязательно является концом полуинтервала
  auto right = lower_bound(range_begin, range_end, upper_bound);
  
  return {left, right};
}
#else
template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith (
  RandomIt range_begin, RandomIt range_end, const string& prefix)
{
  using type = typename RandomIt::value_type;

  auto it_low = std::lower_bound (range_begin, range_end, prefix, 
      [] (type one, type two /*prefix*/) 
      {
        size_t prefix_len = two.size ();
        size_t word_len = one.size ();

        auto res = one.compare (two);
        if (res < 0)
          return true;

        if (prefix_len > word_len && res == 0)
          return true;

        return false;
      });

  auto it_up = std::upper_bound (range_begin, range_end, prefix, 
      [prefix] (type two /*prefix*/, type one) 
      {
        size_t prefix_len = two.size ();
        size_t word_len = one.size ();

        auto res = one.compare (two);
        if (res < 0)
          return false;

        if (prefix_len > word_len && res == 0)
          return false;

        res = one.compare (0, prefix_len, two, 0, prefix_len);

        if (res == 0)
          return false;

        return true;
      });

  return {it_low, it_up};
}
#endif

int main () 
{
  const vector<string> sorted_strings = {"m", "mo", "moscow", "motovilikha", "murmansk"};

  const auto mo_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
  for (auto it = mo_result.first; it != mo_result.second; ++it)
    cout << *it << " ";
  cout << endl;

  cout << (mo_result.first - begin(sorted_strings)) << " " <<
    (mo_result.second - begin(sorted_strings)) << endl;
  
  
  const auto mt_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
  cout << (mt_result.first - begin(sorted_strings)) << " " <<
      (mt_result.second - begin(sorted_strings)) << endl;
  
  const auto na_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
  cout << (na_result.first - begin(sorted_strings)) << " " <<
      (na_result.second - begin(sorted_strings)) << endl;
  
  const auto ao_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "ao");
  cout << (ao_result.first - begin(sorted_strings)) << " " <<
      (ao_result.second - begin(sorted_strings)) << endl;

  const auto m_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "a");
  cout << (m_result.first - begin(sorted_strings)) << " " <<
      (m_result.second - begin(sorted_strings)) << endl;

  return 0;
}