#include "date.h"
#include "node.h"
#include "database.h"
#include "condition_parser.h"

#include "test_db.h"

#include <iostream>
#include <stdexcept>

#include <vector>

using namespace std;

int main ()
{
  TestAll ();

  Database db;

  for (string line; getline (cin, line); )
    {
      istringstream is (line);

      string command;
      is >> command;
      if (command == "Add")
        {
          const auto date = ParseDate (is);
          const auto event = ParseEvent (is);
          db.Add (date, event);
        }
      else if (command == "Print")
        db.Print (cout);
      else if (command == "Del")
        {
          auto condition = ParseCondition (is);
          auto predicate = [condition] (const Date & date, const string & event)
          { return condition->Evaluate (date, event); };

          int count = db.RemoveIf (predicate);
          cout << "Removed " << count << " entries" << endl;
        }
      else if (command == "Find")
        {
          auto condition = ParseCondition (is);
          auto predicate = [condition] (const Date & date, const string & event)
          { return condition->Evaluate (date, event); };

          const auto entries = db.FindIf (predicate);
          for (const auto& entry : entries)
            cout << entry << endl;

          cout << "Found " << entries.size () << " entries" << endl;
        }
      else if (command == "Last")
        {
          try
          {
            const auto date = ParseDate (is);
            cout << db.Last (date) << endl;
          }
          catch (invalid_argument&)
          {
            cout << "No entries" << endl;
          }
        }
      else if (command.empty ())
        continue;
      else
        throw logic_error ("Unknown command: " + command);
    }

  return 0;
}
