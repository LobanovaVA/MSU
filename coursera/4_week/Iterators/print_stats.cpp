#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

#ifdef MY
enum class Gender 
{
  FEMALE,
  MALE
};

struct Person 
{
  int age;
  Gender gender;
  bool is_employed;
};

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
  if (range_begin == range_end) {
    return 0;
  }
  vector<typename InputIt::value_type> range_copy(range_begin, range_end);
  auto middle = begin(range_copy) + range_copy.size() / 2;
  nth_element(
      begin(range_copy), middle, end(range_copy),
      [](const Person& lhs, const Person& rhs) {
        return lhs.age < rhs.age;
      }
  );
  return middle->age;
}
#endif 

void PrintStats (vector<Person> persons)
{
  int ans = ComputeMedianAge (persons.begin (), persons.end ());
  cout << "Median age = " << ans << endl;

  auto it = std::partition (persons.begin (), persons.end(), 
    [] (Person i) { return i.gender == Gender::FEMALE; } );
  ans = ComputeMedianAge (persons.begin (), it);
  cout << "Median age for females = " << ans << endl;

  it = std::partition (persons.begin (), persons.end(), 
    [] (Person i) { return i.gender == Gender::MALE; } );
  ans = ComputeMedianAge (persons.begin (), it);
  cout << "Median age for males = " << ans << endl;

  it = std::partition (persons.begin (), persons.end(), 
    [] (Person i) { return i.gender == Gender::FEMALE 
                         && i.is_employed; } );
  ans = ComputeMedianAge (persons.begin (), it);
  cout << "Median age for employed females = " << ans << endl;

  it = std::partition (persons.begin (), persons.end(), 
    [] (Person i) { return i.gender == Gender::FEMALE
                         && !i.is_employed; } );
  ans = ComputeMedianAge (persons.begin (), it);
  cout << "Median age for unemployed females = " << ans << endl;

  it = std::partition (persons.begin (), persons.end(), 
    [] (Person i) { return i.gender == Gender::MALE 
                         && i.is_employed; } );
  ans = ComputeMedianAge (persons.begin (), it);
  cout << "Median age for employed males = " << ans << endl;

  it = std::partition (persons.begin (), persons.end(), 
    [] (Person i) { return i.gender == Gender::MALE
                         && !i.is_employed; } );
  ans = ComputeMedianAge (persons.begin (), it);
  cout << "Median age for unemployed males = " << ans << endl;
}

int main () 
{
  vector<Person> persons = {
      {31, Gender::MALE, false},
      {40, Gender::FEMALE, true},
      {24, Gender::MALE, true},
      {20, Gender::FEMALE, true},
      {80, Gender::FEMALE, false},
      {78, Gender::MALE, false},
      {10, Gender::FEMALE, false},
      {55, Gender::MALE, true},
  };

  PrintStats (persons);
  return 0;
}
