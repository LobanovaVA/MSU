#include "student.h"

student::student(const char * name, int value)
{init(name, value);}

student::~student()
{destroy();}

int student::init(const char * name, int value)
{
  if(name)
  {
    this -> name = new char[strlen(name) + 1];
    if(!name) {return 0;}
    strcpy(this -> name, name);
  }
  else
  {this -> name = 0;}
  this -> value = value;
  return 1;
}

void student::destroy()
{if(name) {delete [] name; name = 0;} value = 0;}

student::student(const student & rhs)
{init(rhs.name, rhs.value);}

student & student::operator = (const student & rhs)
{destroy(); init(rhs.name, rhs.value); return * this;}

student & student::move(student & rhs)
{
  if(this == &rhs) {return * this;}
  destroy();
  name = rhs.name;
  value = rhs.value;
  rhs.name = 0;
  return * this;
}

int student::setName(const char * name)
{
  if(this -> name) {delete [] this -> name; this -> name = 0;}
  if(this -> name)
  {
    this -> name = new char[strlen(name) + 1];
    if(!this -> name) {return -1;}
    strcpy(this -> name, name);
  }
  else 
  {this -> name = 0;}
  return 0;
}


void student::swap(student & rhs)
{
  char * st = name; name = rhs.name; rhs.name = st;
  int t = value; value = rhs.value; rhs.value = t;
}

int student::read(FILE * fp)
{
  char buf[LEN];
  int value;
  if(fscanf(fp,"%s %d", buf, &value) != 2) {return 0;}
  destroy();
  return init(buf, value);
}


void student::print(FILE * fp) const
{fprintf(fp, "%s %d", name, value);}


int student::cmp(const student & rhs) const
{
  if(name && rhs.name)
  {
    int res = strcmp(name, rhs.name);
    if(res == 0)
    {return value - rhs.value;}
    return res;
  }
  if(!name && rhs.name)
  {return 0;}
  if(name && !rhs.name)
  {return 1;}
  return value - rhs.value;
}

bool student::operator < (const student & rhs) const {return (cmp(rhs) < 0) ? 1 : 0;}
bool student::operator > (const student & rhs) const {return rhs < * this;}
bool student::operator <= (const student & rhs) const {return !(rhs < * this);}
bool student::operator >= (const student & rhs) const {return !(* this < rhs);}
bool student::operator == (const student & rhs) const {return (cmp(rhs) == 0) ? 1 : 0;}
bool student::operator != (const student & rhs) const {return !(* this == rhs);}
