#include <iostream>
#include <vector>

#include <tuple>
#include <map>

using namespace std;

#ifdef MY
enum class Lang { DE, FR, IT };

struct Region 
{
  string std_name;
  string parent_std_name;
  map<Lang, string> names;
  int64_t population;
};

ostream&
operator<< (ostream &out, const Region &M)
{
  out << "   " << M.std_name << " " << M.parent_std_name << " " << M.population << endl;
  out << "   " << M.names.at (Lang::DE) << " " << M.names.at (Lang::FR) << " " 
               << M.names.at (Lang::IT) << endl;
  out << endl;
  return out;
}
#endif

tuple<const string, const string, const int64_t, const string, const string, const string> 
Get (const Region &R)
{ 
  return { 
    R.std_name, R.parent_std_name, R.population,
    (R.names.count (Lang::DE) == 1) ? R.names.at (Lang::DE) : "",
    (R.names.count (Lang::FR) == 1) ? R.names.at (Lang::FR) : "", 
    (R.names.count (Lang::IT) == 1) ? R.names.at (Lang::IT) : ""}; 
}  

bool operator< (const Region &one, const Region &two)
{
  return Get (one) < Get (two); 
}

/* Какое максимальное количество повторов.
 * Две записи считаются различными, если они отличаются хотя бы одним полем. */
int 
FindMaxRepetitionCount (const vector<Region> & regions)
{
  map <Region, int> ans;
  for (auto it : regions)
    ans[it]++;

  int count = 0;
  for (auto & [key, value] : ans)
    count = max (count, value);

  return count;
}

#ifdef MY
int main() {
  cout << FindMaxRepetitionCount({
      {"Moscow", "Russia",  {{Lang::DE, "Moskau"},   {Lang::IT, "Mosca"}}, 89}, 
      {"Russia", "Eurasia", {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}}, 89}, 
      {"Moscow", "Russia",  {{Lang::DE, "Moskau"},   {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},  89}, 
      {"Moscow", "Russia",  {{Lang::DE, "Moskau"},   {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},  89}, 
      {"Russia", "Eurasia", {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}}, 89},
  }) << endl;
  
  cout << FindMaxRepetitionCount({
      {"Moscow", "Russia",   {{Lang::DE, "Moskau"},   {Lang::FR, "Moscou"},   {Lang::IT, "Mosca"}},  89}, 
      {"Russia", "Eurasia",  {{Lang::DE, "Russland"}, {Lang::FR, "Russie"},   {Lang::IT, "Russia"}}, 89}, 
      {"Moscow", "Russia",   {{Lang::DE, "Moskau"},   {Lang::FR, "Moscou d"}, {Lang::IT, "Mosca"}},  89}, 
      {"Moscow", "Toulouse", {{Lang::DE, "Moskau"},   {Lang::FR, "Moscou"},   {Lang::IT, "Mosca"}},  89}, 
      {"Moscow", "Russia",   {{Lang::DE, "Moskau"},   {Lang::FR, "Moscou"},   {Lang::IT, "Mosca"}},  31},
  }) << endl;
  
  return 0;
}
#endif

