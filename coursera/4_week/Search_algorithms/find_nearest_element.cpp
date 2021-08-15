#include <iostream>
#include <set>

using namespace std;

#ifdef COURSERA
set<int>::const_iterator FindNearestElement(const set<int>& numbers,
                                            int border) {
  // Запрашиваем итератор на первый элемент, не меньший border;
  // если такого элемента нет, то мы получим numbers.end()
  const auto first_not_less = numbers.lower_bound(border);

  // Если множество пусто или до первого элемента не меньше border
  // нет элементов, то мы уже получили ответ
  if (first_not_less == numbers.begin()) {
    return first_not_less;
  }

  // Если элементов, не меньших border, нет и set не пуст, то достаточно взять
  // итератор на последний элемент, меньший border
  const auto last_less = prev(first_not_less);
  if (first_not_less == numbers.end()) {
    return last_less;
  }

  // Разыменуем оба итератора-кандидата и выберем тот,
  // чей элемент ближе к искомому
  const bool is_left = (border - *last_less <= *first_not_less - border);
  return is_left ? last_less : first_not_less;
}

#else
set<int>::const_iterator 
FindNearestElement (const set<int>& numbers, int border)
{
  auto res = numbers.equal_range (border);

  if (res.first == res.second) // if border is not in set
  {
  	auto it = res.second;

  	if (it == numbers.begin ())
  	  return it;

  	auto it_less = --res.first;

  	if (it == numbers.end ())
  	  return it_less;

  	if (border - *it_less <= *it - border)
  	  return  it_less;

  	return it;
  }

  if (res.second == numbers.end ())
  	return res.first;

  if (border == *res.first)
  	return res.first;

  return  res.second;
}
#endif

int main () 
{
  set<int> numbers = {1, 4, 6};
  cout <<
      *FindNearestElement (numbers, 0) << endl <<
      *FindNearestElement (numbers, 3) << endl <<
      *FindNearestElement (numbers, 5) << endl <<
      *FindNearestElement (numbers, 6) << endl <<
      *FindNearestElement (numbers, 100) << endl;
      
  set<int> empty_set;
  
  cout << (FindNearestElement (empty_set, 8) == end (empty_set)) << endl;
  return 0;
}