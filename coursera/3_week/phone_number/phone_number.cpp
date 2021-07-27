#include <sstream>
#include "phone_number.h"

using namespace std;

#ifdef COURSERA
PhoneNumber::PhoneNumber(const string& international_number) {
  istringstream is(international_number);

  char sign = is.get();
  getline(is, country_code_, '-');
  getline(is, city_code_, '-');
  getline(is, local_number_);

  if (sign != '+' || country_code_.empty() || city_code_.empty() || local_number_.empty()) {
    throw invalid_argument("Phone number must begin with '+' symbol and contain 3 parts separated by '-' symbol: " + international_number);
  }
}
#else
string cut (size_t & prev, size_t & curr, const string &international_number, bool last = false)
{
  prev = curr + 1;
  curr = international_number.find ("-", prev);

  if (curr == prev)
    throw std::invalid_argument ("curr == prev");

  if (!last && curr == std::string::npos)
    throw std::invalid_argument ("without any part");

  return international_number.substr (prev, curr - prev);
}

PhoneNumber::PhoneNumber (const string &international_number)
{
  size_t prev = 0, curr = 0;

  if (international_number[0] != '+')
    throw std::invalid_argument ("without +");

  country_code_ = cut (prev, curr, international_number);
  city_code_    = cut (prev, curr, international_number);

  cut (prev, curr, international_number, true);
  local_number_ = international_number.substr (prev);
}
#endif

string 
PhoneNumber::GetCountryCode () const
{
  return country_code_;
}

string 
PhoneNumber::GetCityCode () const
{
  return city_code_;
}

string 
PhoneNumber::GetLocalNumber () const
{
  return local_number_;
}

string 
PhoneNumber::GetInternationalNumber () const
{
  ostringstream os;
  os << "+" << country_code_ << "-" << city_code_ << "-" << local_number_;
  return os.str ();
}

#ifdef MY
#include <iostream>

void test (string tel)
{
  cout << tel << endl;
  PhoneNumber p (tel);
  cout << "Country " << p.GetCountryCode () << endl;
  cout << "City    " << p.GetCityCode () << endl;
  cout << "Local   " << p.GetLocalNumber () << endl;
  cout << p.GetInternationalNumber () << endl;
  cout << endl;
}

int main ()
{
  test ("+7-495-111-22-33");
  test ("+7-495-1112233");
  test ("+1-2-333");
  
  test ("+--");
  // test ("+7");
  // test ("+7-1233");
  // test ("1-2-333");

  return 0;
}
#endif