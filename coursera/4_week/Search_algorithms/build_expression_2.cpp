#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool need_brackets (const char prev, const char oper)
{
  if (prev == '+' || prev == '-')
    if (oper == '*' || oper == '/')
      return true;

  return false;
}

void add_brackets (string &ans, int &first_bracket)
{
  // ans.insert (0, std::string("("));
  first_bracket++;
  ans.insert (ans.size (), std::string(")"));
}

void add_oper (string &ans, const char oper, const int number)
{
  string add = std::string(" ") + oper 
             + std::string(" ") + std::to_string (number);

  ans.insert (ans.size (), add);
}

int main () 
{
  int N, steps_count, number, first_bracket = 0;
  char oper, prev;

  cin >> N >> steps_count;
  std::string ans = std::to_string (N);

  if (steps_count)
  {
    cin >> oper >> number;
    add_oper (ans, oper, number);
    prev = oper;

    for (int i = 1; i < steps_count; i++)
    {
      cin >> oper >> number;
      if (need_brackets (prev, oper))
        add_brackets (ans, first_bracket);

      add_oper (ans, oper, number);
      prev = oper;
    } 
  }

  std::string first_spaces;
  first_spaces.assign(first_bracket, '(');

  cout << first_spaces << ans << endl;
  return 0;
}

/*
  deque<string> expression;
  expression.push_back(to_string(initial_number));
  // первое число никогда не обрамляется скобками
  char last_type = '*';
  for (const auto& operation : operations) 
  {
    // Если условия удовлетворены, обрамляем последовательность скобками
    if (NeedBrackets(last_type, operation.type)) {
      expression.push_front("(");
      expression.push_back(")");
    }
    expression.push_back(" ");
    expression.push_back(string(1, operation.type));
    expression.push_back(" ");
    expression.push_back(to_string(operation.number));

    last_type = operation.type;
  }

  for (const string& s : expression) 
    cout << s;
*/