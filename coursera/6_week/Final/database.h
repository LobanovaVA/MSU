#pragma once

#include <sstream>
#include <algorithm>

#include <utility>
#include <vector>
#include <set>
#include <map>


#include "date.h"

using namespace std;

class Database
{
private:
  map <Date, vector<string>> base;
  set<pair<Date, string>> records;

public:
  void Add (const Date & date, const string & event);
  void Print (ostream & os) const;
  string Last (Date date) const;

  template<class Predicate>
  int RemoveIf (Predicate p);

  template<class Predicate>
  vector<string> FindIf (Predicate p) const;
};

template<class Predicate>
int
Database::RemoveIf (Predicate p)
{
  int count = 0;

  for (auto it = base.begin (); it != base.end (); )
    {
      Date date = it->first;
      vector<string> & vec = it->second;

      auto del_it = stable_partition (
            vec.begin (), vec.end (), [date, p] (string event) { return !p (date, event); });

      if (del_it == vec.begin ())
        it = base.erase (it);
      else
        {
          vec.erase (del_it, vec.end ());
          ++it;
        }
    }

  for (auto it = records.begin (); it != records.end (); )
    {
      if (p (it->first, it->second))
        {
          count++;
          it = records.erase (it);
        }
      else
        ++it;
    }

  return count;
}


template<class Predicate>
vector<string>
Database::FindIf (Predicate p) const
{
  vector<string> result;
  ostringstream os;

  for (const auto & [date, vect] : base)
    {
      for (const auto & event : vect)
        if (p (date, event))
          {
            os << date << " " << event;
            result.push_back (os.str ());
            os.str ("");
          }
    }

  return result;
}
