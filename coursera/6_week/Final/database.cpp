#include "database.h"

using namespace std;

void
Database::Add (const Date & date, const string & event)
{
  if (records.count ({date, event}) == 1)
    return;

  records.insert ({date, event});
  base[date].push_back (event);
}

void
Database::Print (ostream & os) const
{
  for (const auto & [date, vec] : base)
    {
      for (const auto & event : vec)
        os << date << " " << event << endl;
    }
}

string
Database::Last (Date date) const
{
  auto it = base.upper_bound (date);
  if (it == base.begin ())
      throw std::invalid_argument("in_Last");

  --it;

  ostringstream os;
  auto vec = it->second;

  os << it->first << " " << vec[vec.size () - 1];
  return os.str ();
}
