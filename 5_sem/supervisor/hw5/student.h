#include "addition.h"
#ifndef STUDENT_H
#define STUDENT_H

class student 
{   
private:
  std::unique_ptr <char []> name = nullptr;
  int value = 0;

public:
  student () = default;
  student (const char* new_name, int new_value);
  ~student () = default;

  void set_value (int new_value);
  int set_name (const char* new_name);
  int init (const char* new_name, int new_value);

  int get_value () const;
  int get_length () const;
  char * get_name () const;

  int read (FILE* fp);
  void print ();

  int operator< (const student& x);

};

#endif


//student (const student& x);
//student (student&& x);
//student& operator= (const student& x);
//student& operator= (student&& x);
//int operator< (const student& x);
//int operator> (const student& x);
//void copy(const student &x);
//void destroy ();
//void swap (student& x);
