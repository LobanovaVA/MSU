#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void add (string &ans, char oper, int number)
{
  ans.insert (0, std::string("("));
  ans.insert (ans.size (), std::string(")"));

  string add = std::string(" ") + oper 
             + std::string(" ") + std::to_string (number);

  ans.insert (ans.size (), add);
}

int main () 
{
  int N, steps_count, number;
  char oper;

  cin >> N >> steps_count;
  std::string ans = std::to_string (N);

  for (int i = 0; i < steps_count; i++)
  {
    cin >> oper >> number;
    add (ans, oper, number);
  } 

  cout << ans << endl;
  return 0;
}