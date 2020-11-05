#include "record.h"
#include "addition.h"

#define LEN 1234

record::record (const record& x)
{
    init(x.get_name(), x.phone, x.group);
}

record::record (record&& x)
{
    phone = x.phone;
    group = x.group;
    name = std::move (x.name);
    x.phone = x.group = 0;
    x.name = nullptr;
}

record& record::operator= (const record& x)
{
    (this)->~record();
    init(x.get_name(), x.phone, x.group);
    return *this;
}

record& record::operator= (record&& x)
{
    phone = x.phone;
    group = x.group;
    name = std::move (x.name);
    x.phone = x.group = 0;
    x.name = nullptr;
    return *this;
}

int record::operator== (const record& x)
{
    if (!strcmp ((this)->get_name(), x.get_name()) && phone == x.phone && group == x.group) return 1;
    else return 0;
}

int record::read (FILE* fp)
{
    char buff[LEN];
    (this) -> ~record();
    if (fscanf (fp, "%s %d %d", buff, &phone, &group) != 3)
    {
        if (feof(fp)) return ERROR_END_OF_INPUT_FILE;
        return ERROR_READ_A;
    }
    if (init (buff, phone, group)) return ERROR_READ_CLASS ;
    return 0;
}

void record::print (FILE* out)
{
    if(!name) fprintf(out, " %d %d\n",  phone, group);
    else fprintf(out, "%s %d %d\n", (this)->get_name(), phone, group);
}


int record::init (const char* n, int p, int g)
{
    phone = p; group = g;
    if (n)
    {
        name = std::unique_ptr <char [ ]> (new char [strlen (n) + 1]);
        if ( !name ) return ERROR_READ_CLASS;
        strcpy (name.get(), n);
    }
    else name = nullptr;
    return 0;
}


