#include <iostream>
#include <string>
#include <map>

using namespace std;

string find (const map<int, string>& names, int year);

class Person 
{
  map<int, string> first_names;
  map<int, string> last_names;

public:
  void ChangeFirstName (int year, const string& new_first_name) 
  {
    first_names[year] = new_first_name;
  }

  void ChangeLastName(int year, const string& new_last_name) 
  {
    last_names[year] = new_last_name;
  }

  string GetFullName(int year) 
  {
    const string first_name = find (first_names, year);
    const string last_name  = find (last_names,  year);

    if (first_name.empty() && last_name.empty()) 
      return "Incognito";

    if (last_name.empty())
      return first_name + " with unknown last name";

    if (first_name.empty()) 
      return last_name + " with unknown first name";

    return first_name + " " + last_name;
  }
};

string find (const map<int, string>& names, int year)
 {
  auto it = names.upper_bound (year);
  string name;

  if (it != names.begin ()) 
    name = prev (it)->second;
  
  return name;
}

int main() {
  Person person;
  
  person.ChangeFirstName (1965, "Polina");
  person.ChangeLastName (1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) 
    cout << person.GetFullName(year) << endl;
  
  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) 
    cout << person.GetFullName(year) << endl;
  
  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) 
    cout << person.GetFullName(year) << endl;
  
  return 0;
}