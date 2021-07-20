#include <iostream>
#include <vector>

#include <tuple>
#include <utility> // for pair

#include <map>
#include <set>

using namespace std;

struct Date
{
  int year;
  int month;
  int day;  
};

bool operator< (const Date &lhs, const Date &rhs)
{
  return vector<int> {lhs.year, lhs.month, lhs.day}
       < vector<int> {rhs.year, rhs.month, rhs.day};
}


struct Date2
{
  int year;
  string month;
  int day;  
};

bool operator< (const Date2 &lhs, const Date2 &rhs)
{
  tuple<const int&, const string&, const int&> lhs_key =
    tie (lhs.year, lhs.month, lhs.day);

  return tie (lhs.year, lhs.month, lhs.day)
       < tie (rhs.year, rhs.month, rhs.day);
}

int main_v1 () 
{
  cout << " === v1 === " << endl;

  cout << "With vector: " << (Date {2017, 6, 8} < Date {2017, 1, 26}) << endl;
  cout << "With tie:    " << (Date2 {2017, "June", 8} < Date2 {2017, "Janury", 26}) << endl;
  
  cout << endl;
  return 0;
}


int main_v2 () 
{
  cout << " === v2 === " << endl;

  tuple<int, string, bool> t1 (7, "C++", true);

  auto t2 = make_tuple (7, "C++", true);
  cout << "Get 1st elem of tuple t2 : " << get<1>(t2) << endl;

  tuple t3 (7, "C++", true);   //need --std=c++1z
  cout << "Get 1st elem of tuple t3 : " << get<1>(t3) << endl;

  cout << endl;

  pair<int, string> p1 (7, "C++");
  cout << "Get elems of pair : " << p1.first << " " << p1.second << endl;
  auto p2 = make_pair (7, "C++");
  cout << "Get elems of pair : " << p2.first << " " << p2.second << endl;

  cout << endl;

  map<int, string> digits = {{1, "first"}};
  for (const auto & item : digits)
    cout << item.first << " " << item.second << endl;

  for (const auto & [key, value] : digits) //need --std=c++1z
    cout << key << " " << value << endl;

  cout << endl;
  return 0;
}


class  Cities
{
  map<string, string> city_to_country;
  set<string> ambiguos_cities;

public:
  tuple<bool, string> FindCountry (const string& city) const
  {
    if (city_to_country.count (city) == 1)
      return {true, city_to_country.at (city)};
    else if (ambiguos_cities.count (city) == 1)
      return {false, "Ambiguos"};
    else 
      return {false, "Not exist"};
  }
};

int main_v3 () 
{
  cout << " === v3 === " << endl;

  Cities cities;
  auto t = cities.FindCountry ("Volgograd");
  cout << "1st elem of tuple : " << get<1>(t) << endl;
  
  bool success;
  string message;
  // tuple <bool &, string &>
  tie (success, message) = cities.FindCountry ("Volgograd");
  cout << success << " " << message << endl;
  
  auto [sucs, msg] = cities.FindCountry ("Volgograd");
  cout << sucs << " " << msg << endl;
  
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