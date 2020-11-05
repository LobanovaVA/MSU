#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>

class student 
{   
    private:
        char *name = nullptr;
        int value = 0;
    public:
        student () = default;
        student (const student& x);
        student (student&& x);
        ~student ();

        int read (FILE* fp);
        void print (FILE* out = stdout);

//navigation:
        const char* get_name () const {    return (const char*)name;   }
        int get_value () const {  return value;   }

//adding:
        int init (const char* n, int v);

//deleting:
        void destroy ();

//operators:
        student& operator= (const student& x);
        student& operator= (student&& x);
        int operator< (const student& x);
        int operator> (const student& x);  

//other:
        void swap (student& x);
        void copy(const student &x);
         
};
#endif
