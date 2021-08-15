#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <algorithm>
#include <numeric>
#include <iomanip>

constexpr int SEC = 86400;
constexpr int SIZE = 73200;
static std::tm TIME = {0,0,0,0,0,0};
static std::time_t DEFT = std::mktime(&TIME);
using namespace std;


enum class QueryType 
{
  Income,
  Earn
};

struct Date 
{
  std::time_t from;
  std::time_t to;

  int get_days () const
  {
    double sec = std::difftime (to, from);
    return 1 + static_cast<int> (sec / SEC);
  }

  int get_inds () const
  {
    double sec = std::difftime (from, DEFT);
    return static_cast<int> (sec / SEC);
  }
};

std::time_t get_date (int year, int month, int day)
{
  std::tm tm = {0,0,0,0,0,0}; 

  tm.tm_year = year - 1900;
  tm.tm_mon  = month - 1;
  tm.tm_mday = day;

  return std::mktime (&tm); 
}

istream& operator >> (istream& is, Date& d)
{
  int year, month, day;
  char s;

  is >> year >> s >> month >> s >> day;
  d.from = get_date (year, month, day);

  is >> year >> s >> month >> s >> day;
  d.to = get_date (year, month, day);

  return is;
}

struct Query 
{
  QueryType type;
  Date date;
  int value;
};

istream& operator >> (istream& is, Query& q) 
{
  string type;
  is >> type;

  if (type == "ComputeIncome")
  {
    q.type = QueryType::Income;
    is >> q.date;
  }
  else
  {
    q.type = QueryType::Earn;
    is >> q.date >> q.value;
  }

  return is;
}

class Manager 
{
private:
  vector<double> v;

public:
  Manager () { v.assign (SIZE, 0); }

  ~Manager () = default;

  void AddEarn (const Date& date, int value) 
  {
    int days = date.get_days ();
    double each_value = static_cast<double> (value) / days;
   
    int ind = date.get_inds ();
    for (int i = ind; i < ind + days; i++)
      v[i] += each_value;

  }

  double GetComputeIncome (const Date& date) const 
  {
    int days = date.get_days ();
    int ind = date.get_inds ();

    double sum = std::accumulate 
        (v.begin() + ind, v.begin() + ind + days, 0.0);

    return sum;
  }

};


int main () 
{
  int query_count;
  Query q;
  Manager M;

  cin >> query_count;
  for (int i = 0; i < query_count; i++)
  {
    cin >> q;
    switch (q.type) 
    {
      case QueryType::Income:
        cout << std::setprecision (25) << M.GetComputeIncome (q.date) << endl;
        break;
      case QueryType::Earn:
        M.AddEarn (q.date, q.value);
        break;
    }
  }

  return 0;
}
