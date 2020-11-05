#include "student.h"
#include "addition.h"

#include <stdio.h>
#include <string.h>
#include <iostream>

#define LEN 1234

student::student (const student& x)
{	
	init(x.name, x.value);     
}

student::student (student&& x)
{
	value = x.value;
	name  = x.name;
	x.value = 0;
	x.name = nullptr;
}

student::~student ()
{	
	destroy ();    
}


student& student::operator= (const student& x)
{
	destroy ();
	init (x.name, x.value);
	return *this;
}

student& student::operator= (student&& x)
{
	destroy ();
	value = x.value;
	name = x.name;
	x.value = 0;
	x.name = nullptr;
	return *this;
}

int student::operator< (const student& x)
{
	if (!name && !x.name) return value < x.value;
	if (!name) return 1;
	if (!x.name) return 0;
	int res = strcmp (name, x.name);
	if (res < 0) return 1;
	if (res > 0) return 0;
	return value < x.value;
}

int student::operator> (const student& x)
{
	if (!name && !x.name) return value > x.value;
	if (!name) return 0;
	if (!x.name) return 1;
        int res = strcmp (name, x.name);
	if (res < 0) return 0;
	if (res > 0) return 1;
	return value > x.value;
}



int student::read (FILE* fp)
{
	char buff[LEN];
	destroy ();
    if (fscanf (fp, "%s %d", buff, &value) != 2)
    {
        if (feof(fp)) return 1;
        return ERROR_CANNOT_READ_INPUT_FILE;
	}
    if (init(buff, value)) return ERROR_CANNOT_READ_CLASS ;
	return 0;
}

void student::print (FILE* out)
{    
	fprintf(out, "%s %d\n", name, value);    
}

void student::swap (student& x)
{
	int tmp = value;
	value = x.value;
	x.value = tmp;

	char* buff = name;
	name = x.name;
    x.name = buff;
}



int student::init (const char* n, int v)
{
	value = v;
	if (n)
	{   
        name = new char[strlen (n) + 1];
		if ( !name ) return ERROR_CANNOT_READ_CLASS;
		strcpy (name, n);
	}
	else
        name = nullptr;
    return 0;
}

void student::destroy ()
{
	if (name)
	{
		delete []name;
        name = nullptr;
	}
	value = 0;
}

void student::copy(const student &x)
{
    name=x.name;
    value=x.value;
}
