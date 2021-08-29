#include "date.h"

#include <sstream>
#include <iomanip>
#include <algorithm>
#include <vector>

using namespace std;

Date ParseDate (istream & is)
{
  int year, month, day;
  char s;

  is >> year >> s >> month >> s >> day;
  return {year, month, day};
}

string ParseEvent (istream& is)
{
  string event;
  getline (is, event);

  if (!event.empty ())
    {
      long unsigned int i = 0;
      while (i < event.size () && event[i] == ' ')
        i++;
      event.erase (0, i);
    }

  return event;
}

ostream& operator << (ostream & os, const Date & date)
{
  os << setw (4) << setfill ('0') << date.get_year  () << "-";
  os << setw (2) << setfill ('0') << date.get_month () << "-";
  os << setw (2) << setfill ('0') << date.get_day   ();

  return os;
}

bool operator<  (const Date & lhs, const Date & rhs)
{
  return vector<int> {lhs.get_year (), lhs.get_month (), lhs.get_day ()}
       < vector<int> {rhs.get_year (), rhs.get_month (), rhs.get_day ()};
}

bool operator<= (const Date & lhs, const Date & rhs)
{
  return vector<int> {lhs.get_year (), lhs.get_month (), lhs.get_day ()}
      <= vector<int> {rhs.get_year (), rhs.get_month (), rhs.get_day ()};
}

bool operator>  (const Date & lhs, const Date & rhs)
{
  return vector<int> {lhs.get_year (), lhs.get_month (), lhs.get_day ()}
       > vector<int> {rhs.get_year (), rhs.get_month (), rhs.get_day ()};
}

bool operator>= (const Date & lhs, const Date & rhs)
{
  return vector<int> {lhs.get_year (), lhs.get_month (), lhs.get_day ()}
      >= vector<int> {rhs.get_year (), rhs.get_month (), rhs.get_day ()};
}

bool operator== (const Date & lhs, const Date & rhs)
{
  return vector<int> {lhs.get_year (), lhs.get_month (), lhs.get_day ()}
      == vector<int> {rhs.get_year (), rhs.get_month (), rhs.get_day ()};
}

bool operator!= (const Date & lhs, const Date & rhs)
{
  return vector<int> {lhs.get_year (), lhs.get_month (), lhs.get_day ()}
      != vector<int> {rhs.get_year (), rhs.get_month (), rhs.get_day ()};
}
