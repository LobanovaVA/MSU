#include <stdio.h>
#ifndef STUDENT_H
#define STUDENT_H
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

        student& operator= (const student& x);
        student& operator= (student&& x);
        int operator< (const student& x);
        int operator> (const student& x);
        void copy(const student &x);
        
		const char* get_name () const {    return (const char*)name;   }
		int get_value () const {  return value;   }
        int init (const char* n, int v);
        void destroy ();
        
        int read (FILE*);
        void print (FILE* out = stdout);
        void swap (student& x);
};
#endif
