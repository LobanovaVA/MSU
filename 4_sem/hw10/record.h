#ifndef RECORD
#define RECORD

#include "addition.h"

class record
{
private:
    std::unique_ptr <char [ ]> name = nullptr;
    int phone = -1;
    int group = -1;
public:
    friend class command;
    record () = default;
   //~record () = default;
    record (const record& x);
    record (record&& x);
    ~record () { name = nullptr; phone = group = -1; };

    record& operator= (const record& x);
    record& operator= (record&& x);
    int operator== (const record& x);
    int operator< (const record& x);
    void copy(const record &x);

    char* get_name () const { return name.get();}
    int get_phone () const {  return phone;   }
    int get_group () const {  return group;   }
    int init (const char* n, int p, int g);

    int read (FILE*);
    void print (FILE* out = stdout);
    void Print (int fd);

};

#endif
