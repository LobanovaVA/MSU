#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<string> SplitIntoWords (const string& s)
{
  vector<string> ans;

  size_t prev = 0;
  size_t curr = s.find (' ');

  ans.push_back ({s, prev, curr - prev});

  while (curr != std::string::npos)
  {
    prev = curr + 1;
    curr = s.find (' ', prev);
    ans.push_back ({s, prev , curr - prev});
  }

  return ans;
}

int main () 
{
  string s = "C";//"C Cpp Java Python";

  vector<string> words = SplitIntoWords (s);
  cout << words.size () << " ";
  for (auto it = begin (words); it != end (words); ++it) 
  {
    if (it != begin(words)) 
      cout << "/";
    
    cout << *it;
  }

  cout << endl;
  return 0;
}
