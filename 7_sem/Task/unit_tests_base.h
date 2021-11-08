#ifndef UNIT_TESTS_BASE_H
#define UNIT_TESTS_BASE_H

#include <sstream>
#include <iostream>
#include <exception>
#include <string>
#include <cmath>

constexpr double EPS = 1.e-15;

inline bool is_equal (double x, double y)
{
  return fabs (x - y) < EPS;
}

using namespace std;

template<class T, class U>
void AssertEqual (const T& t, const U& u, const string& hint)
{
  if (t != u)
    {
      ostringstream os;
      os << "Assertion failed: " << t << " != " << u
         << " hint: " << hint;
      throw runtime_error (os.str ());
    }
}

inline void Assert (bool b, const string& hint) {
  AssertEqual (b, true, hint);
}

class TestRunner
{
public:
  template <class TestFunc>
  void RunTest (TestFunc func, const string& test_name)
  {
    try
    {
      func();
      cerr << test_name << " OK" << endl;
    }
    catch (runtime_error& e)
    {
      ++fail_count;
      cerr << test_name << " fail: " << e.what () << endl;
    }
  }

  ~TestRunner ()
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

#endif // UNIT_TESTS_BASE_H
