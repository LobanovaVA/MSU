#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <algorithm>
#include <numeric>
#include <iomanip>

constexpr int SEC = 86400;
constexpr int SIZE = 146400;
static std::tm TIME = {0,0,0,-200,0,1};
static std::time_t DEFT = std::mktime(&TIME);
using namespace std;

std::time_t get_date (int year, int month, int day)
{
  std::tm tm = {0,0,0,0,0,0}; 

  tm.tm_year = year - 1900;
  tm.tm_mon  = month - 1;
  tm.tm_mday = day;

  return std::mktime (&tm); 
}

int get_days (const std::time_t& from, const std::time_t& to)
{
    double sec = std::difftime (to, from);
    return static_cast<int> (sec / SEC);
}

static const std::time_t START_DATE = get_date (1700, 01, 01);
static const std::time_t END_DATE = get_date (2100, 01, 01);
static const size_t DAY_COUNT = get_days (END_DATE, START_DATE);

struct Date
{
  std::time_t curr;

  int get_inds () const
  {
    double sec = std::difftime (curr, START_DATE);
    return static_cast<int> (sec / SEC);
  }
};


istream& operator >> (istream& is, Date& d)
{
  int year, month, day;
  char s;

  is >> year >> s >> month >> s >> day;
  d.curr = get_date (year, month, day);

  return is;
}


class Manager 
{
private:
  vector<uint64_t> v;
  vector<uint64_t> p;

public:
  Manager () { v.assign (SIZE, 0); p.assign (SIZE, 0); }

  ~Manager () = default;

  void AddEarn (const Date& date, uint64_t value) 
  {
    int ind = date.get_inds ();
    v[ind] = value;
  }

  void PartialSumm ()
  {
    partial_sum (v.begin (), v.end (), p.begin ());
  }

  uint64_t GetComputeIncome (const Date& from, const Date& to) const 
  {
    int days = get_days (from.curr, to.curr);
    int ind = from.get_inds ();

    return (ind) ? p[ind + days] - p[ind - 1] : p[ind + days];
  }

};


int main () 
{
  int qE_count, qC_count;

  Date date, from, to;
  uint64_t value;

  Manager M;

  cin >> qE_count;
  for (int i = 0; i < qE_count; i++)
  {
    cin >> date >> value;
    M.AddEarn (date, value);
  }

  M.PartialSumm ();

  cin >> qC_count;
  for (int i = 0; i < qC_count; i++)
  {
    cin >> from >> to;
    cout << M.GetComputeIncome (from, to) << endl;
  }

  return 0;
}
