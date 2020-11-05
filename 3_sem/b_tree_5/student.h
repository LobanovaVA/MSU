#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN 1200
#define MAX_PRINT 3
#define MAX_LEN_PRINT 40
#define MAX_HEIGHT_PRINT 3

class student
{
  private:
      char * name;
      int value;
    
  public:
      student(const char * name = 0, int value = 0);
      student(const student & rhs);
      ~student();

      void destroy();
      student & move(student & rhs);

      void swap(student & rhs);
      int init(const char * name, int value);

      int getValue() const;
      void setValue(int value);
      const char * getName() const;
      int setName(const char * name);

      int read(FILE * fp = stdin);
      void print(FILE * fp = stdout)const;

      int cmp(const student & rhs) const;
      bool operator < (const student & rhs) const;
      bool operator > (const student & rhs) const;
      bool operator <= (const student & rhs) const;
      bool operator != (const student & rhs) const;
      bool operator >= (const student & rhs) const;
      bool operator == (const student & rhs) const;
      student & operator = (const student & rhs);
};

