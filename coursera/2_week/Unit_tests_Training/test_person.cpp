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
class Person {
public:
  // Вы можете вставлять сюда различные реализации класса,
  // чтобы проверить, что ваши тесты пропускают корректный код
  // и ловят некорректный
  void ChangeFirstName(int year, const string& first_name) {
  }
  void ChangeLastName(int year, const string& last_name) {
  }
  string GetFullName(int year) {
  }
};
#endif


void Test_change_fisrt_name ()
{
  {
    Person p;
    p.ChangeFirstName (2000, "V");

    AssertEqual(p.GetFullName(1999), "Incognito");
    AssertEqual(p.GetFullName(2001), "V with unknown last name");
  }

  {
    Person p;
    p.ChangeFirstName (2000, "V");
    p.ChangeFirstName (2005, "W");

    AssertEqual(p.GetFullName(1999), "Incognito");
    AssertEqual(p.GetFullName(2003), "V with unknown last name");
    AssertEqual(p.GetFullName(2007), "W with unknown last name");
  }
  {
    Person p;

    p.ChangeFirstName (2000, "V");
    AssertEqual(p.GetFullName(1999), "Incognito");
    AssertEqual(p.GetFullName(2003), "V with unknown last name");

    p.ChangeFirstName (2005, "W");
    AssertEqual(p.GetFullName(1999), "Incognito");
    AssertEqual(p.GetFullName(2003), "V with unknown last name");
    AssertEqual(p.GetFullName(2007), "W with unknown last name");
  }
}


void Test_change_last_name ()
{
  {
    Person p;
    p.ChangeLastName (2000, "V");

    AssertEqual(p.GetFullName(1999), "Incognito");
    AssertEqual(p.GetFullName(2001), "V with unknown first name");
  }

  {
    Person p;
    p.ChangeLastName (2000, "V");
    p.ChangeLastName (2005, "W");

    AssertEqual(p.GetFullName(1999), "Incognito");
    AssertEqual(p.GetFullName(2003), "V with unknown first name");
    AssertEqual(p.GetFullName(2007), "W with unknown first name");
  }
  {
    Person p;

    p.ChangeLastName (2000, "V");
    AssertEqual(p.GetFullName(1999), "Incognito");
    AssertEqual(p.GetFullName(2003), "V with unknown first name");

    p.ChangeLastName (2005, "W");
    AssertEqual(p.GetFullName(1999), "Incognito");
    AssertEqual(p.GetFullName(2003), "V with unknown first name");
    AssertEqual(p.GetFullName(2007), "W with unknown first name");
  }
}


void Test_change_all_name ()
{
  {
    Person p;
    p.ChangeFirstName (2000, "V");
    p.ChangeLastName  (2000, "L");

    AssertEqual(p.GetFullName(1999), "Incognito");
    AssertEqual(p.GetFullName(2001), "V L");
  }

  {
    Person p;
    p.ChangeFirstName (2000, "V");
    p.ChangeLastName  (2005, "L");

    AssertEqual(p.GetFullName(1999), "Incognito");
    AssertEqual(p.GetFullName(2003), "V with unknown last name");
    AssertEqual(p.GetFullName(2007), "V L");
  }

  {
    Person p;
    p.ChangeFirstName (2005, "V");
    p.ChangeLastName  (2000, "L");

    AssertEqual(p.GetFullName(1999), "Incognito");
    AssertEqual(p.GetFullName(2003), "L with unknown first name");
    AssertEqual(p.GetFullName(2007), "V L");
  }

  {
    Person p;
    p.ChangeFirstName (2000, "V");
    p.ChangeLastName  (2005, "L");
    p.ChangeFirstName (2010, "W");
    p.ChangeLastName (2015, "B");

    AssertEqual(p.GetFullName(1999), "Incognito");
    AssertEqual(p.GetFullName(2003), "V with unknown last name");
    AssertEqual(p.GetFullName(2007), "V L");
    AssertEqual(p.GetFullName(2013), "W L");
    AssertEqual(p.GetFullName(2017), "W B");
  }
}


void TestAll ()
{
  TestRunner runner;
  runner.RunTest (Test_change_fisrt_name, "Test_change_fisrt_name");
  runner.RunTest (Test_change_last_name,  "Test_change_last_name");
  runner.RunTest (Test_change_all_name,   "Test_change_all_name");
}

int main() {
  TestAll ();
  return 0;
}
