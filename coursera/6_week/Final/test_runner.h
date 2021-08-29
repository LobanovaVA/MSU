#pragma once

#include <sstream>
#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

template <typename Collection >
string Join (const Collection & c, char d) {
  stringstream ss;
  bool first = true;
  for (const auto& i : c)
    {
      if (! first )
        ss << d;

      first = false;
      ss << i;
    }
  return ss.str ();
}
template <typename First , typename Second >
ostream & operator << ( ostream & out , const pair <First , Second >& p)
{
  return out << '(' <<p. first << ',' << p. second << ')';
}

template <typename T>
ostream & operator << ( ostream & out , const vector <T >& vi)
{
  return out << '[' << Join(vi , ',') << ']';
}

template <typename Key , typename Value >
ostream & operator << ( ostream & out , const map <Key , Value >& m)
{
  return out << '{' << Join(m, ',') << '}';
}


template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint)
{
  if (t != u) {
      ostringstream os;
      os << "Assertion failed: " << t << " != " << u
         << " hint: " << hint;
      throw runtime_error(os.str());
    }
}

inline void Assert(bool b, const string& hint)
{
  AssertEqual(b, true, hint);
}

class TestRunner
{
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name)
  {
    try
    {
      func ();
      cerr << test_name << " OK" << endl;
    }
    catch (runtime_error& e)
    {
      ++fail_count;
      cerr << test_name << " fail: " << e.what () << endl;
    }
  }

  ~TestRunner()
  {
    if (fail_count > 0)
      {
        cerr << fail_count << " unit tests failed. Terminate" << endl;
        exit (1);
      }
  }

private:
  int fail_count = 0;
};
