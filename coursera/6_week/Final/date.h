#pragma once

#include <iostream>

using namespace std;

class Date
{
private:
  int year;
  int month;
  int day;

public:
  Date (int y, int m, int d)
    : year (y), month (m), day (d) {}

  int get_year  () const { return  year;  }
  int get_month () const { return  month; }
  int get_day   () const { return  day;   }
};

Date   ParseDate  (istream & is);
string ParseEvent (istream & is);

ostream& operator << (ostream & os, const Date & date);

bool operator <  (const Date & lhs, const Date & rhs);
bool operator <= (const Date & lhs, const Date & rhs);
bool operator >  (const Date & lhs, const Date & rhs);
bool operator >= (const Date & lhs, const Date & rhs);
bool operator == (const Date & lhs, const Date & rhs);
bool operator != (const Date & lhs, const Date & rhs);

