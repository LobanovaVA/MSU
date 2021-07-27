#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

#ifdef MY
class Rational {
public:
  // Вы можете вставлять сюда различные реализации,
  // чтобы проверить, что ваши тесты пропускают корректный код
  // и ловят некорректный

  Rational();
  Rational(int numerator, int denominator) {
  }

  int Numerator() const {
  }

  int Denominator() const {
  }
};
#endif

void Test_constructor_default ()
{
  Rational r;
  AssertEqual (r.Numerator (), 0, "Numerator = 0");
  AssertEqual (r.Denominator (), 1, "Denominator = 1");
}

void Test_constructor_reduction_of_fractions ()
{
  {
    Rational r (4, 2);
    AssertEqual (r.Numerator (), 2, "Numerator of 4/2 = 2");
    AssertEqual (r.Denominator (), 1, "Denominator of 4/2 = 1");
  }
  {
    Rational r (2, 4);
    AssertEqual (r.Numerator (), 1, "Numerator of 2/4 = 1");
    AssertEqual (r.Denominator (), 2, "Denominator of 2/4 = 2");
  }
  {
    Rational r (1, 4);
    AssertEqual (r.Numerator (), 1, "Numerator of 1/4 = 1");
    AssertEqual (r.Denominator (), 4, "Denominator of 1/4 = 4");
  }
}

void Test_constructor_negative_fractions ()
{
  {
    Rational r (-1, 2);
    Assert (r.Numerator () < 0, "Numerator of -1/2 < 0");
    Assert (r.Denominator () > 0, "Denominator of -1/2 > 0");
  }
  {
    Rational r (1, -2);
    Assert (r.Numerator () < 0, "Numerator of -1/2 < 0");
    Assert (r.Denominator () > 0, "Denominator of -1/2 > 0");
  }
}

void Test_constructor_positive_fractions ()
{
  {
    Rational r (1, 2);
    Assert (r.Numerator () > 0, "Numerator of 1/2 > 0");
    Assert (r.Denominator () > 0, "Denominator of 1/2 > 0");
  }
  {
    Rational r (-1, -2);
    Assert (r.Numerator () > 0, "Numerator of 1/2 > 0");
    Assert (r.Denominator () > 0, "Denominator of -1/2 > 0");
  }
}

void Test_constructor_zero_fractions ()
{
  {
    Rational r (0, 1);
    AssertEqual (r.Numerator (), 0, "Numerator of 0/1 = 0");
    AssertEqual (r.Denominator (), 1, "Denominator of 0/1 = 1");
  }
  {
    Rational r (0, 5);
    AssertEqual (r.Numerator (), 0, "Numerator of 0/5 = 0");
    AssertEqual (r.Denominator (), 1, "Denominator of 0/5 = 1");
  }
  {
    Rational r (0, -5);
    AssertEqual (r.Numerator (), 0, "Numerator of -0/5 = 0");
    AssertEqual (r.Denominator (), 1, "Denominator of -0/5 = 1");
  }
}


void TestAll ()
{
  TestRunner runner;
  runner.RunTest (Test_constructor_default, "Test_constructor_default");
  runner.RunTest (Test_constructor_reduction_of_fractions, "Test_constructor_reduction_of_fractions");
  runner.RunTest (Test_constructor_negative_fractions, "Test_constructor_negative_fractions");
  runner.RunTest (Test_constructor_positive_fractions, "Test_constructor_positive_fractions");
  runner.RunTest (Test_constructor_zero_fractions, "Test_constructor_zero_fractions");
}

int main() {
  TestAll ();
  return 0;
}
