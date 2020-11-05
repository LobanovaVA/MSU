#include <stdio.h>
#include <string.h>
#include <iostream>

#include "student.h"
#include "addition.h"

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
        if (feof(fp)) return ERROR_END_OF_INPUT_FILE;
        return ERROR_CANNOT_READ_INPUT_FILE;
	}
    if (init(buff, value)) return ERROR_CANNOT_READ_CLASS ;
	return 0;
}

void student::print (FILE* out)
{    
    if(!name) fprintf(out, " %d\n", value);
    else fprintf(out, "%s %d\n", name, value);
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


void student::menu ()
{
	char buf[LEN]; 
	print_menu ();
	for(;;)
	{
                printf("\nEnter command: ");
		if (!(fgets (buf, LEN, stdin))) return;
		enum MENU_ITEMS key = (MENU_ITEMS) buf [0];
		switch (key)
		{
                        case MENU_MENU	: {printf("PRINT STUDENT MENU:");		print_menu (); break; }
                        case MENU_PRINT	: {printf("PRINT STUDENT:\n");			print (); break;}
                        case MENU_WORK	: {printf("EDIT STUDENT\n");			edit  (); break;}
                        case MENU_EXIT	: {printf("EXIT INTO PREV STRUCTURE (TREE)\n");  	return;}
		}
	}
}

void student::edit ()
{
        char buf[LEN], buf_n[LEN];
	int v;
        printf("\nInput student name (whithout space!) and value: ");
        if (!(fgets (buf, LEN, stdin))) { printf("Incorrect student name\n");  return; }
        if (sscanf (buf, "%s %d", buf_n, &v) != 2 ) { printf("Incorrect student name\n");  return; }
        destroy ();
        if (init(buf_n, v)) printf("Incorrect student data\n");
} 

/*
void student::edit ()
{
    char buf_n[LEN], buf_v[LEN];
    int v;

    printf("\nInput student name: ");
    if (!(fgets (buf_n, LEN, stdin)))
            { printf("Incorrect student name\n");  return; }
    printf("\nInput student value: ");
    if (!(fgets (buf_v, LEN, stdin)) || (!(v = atoi (buf_v)) && buf_v[0]!='0'))
            { printf("Incorrect student value\n");  return; }
    //if (!(v = atoi (buf_v)) && buf_v[0]!='0') { printf("Incorrect student value\n");  return; }
    buf_n[strlen(buf_n)-1] = '\0';
    destroy ();
    if (init(buf_n, v)) printf("Incorrect student data\n");
} 
*/

void student::print_menu()
{
	printf("\n\n");
        printf("\n               ╔=====🐙 🐯 🐰 🐲 🐢 🐺 🐶 🐷=====╗");
        printf("\n               ║                                 ║");
        printf("\n               ║      STUDENT MENU:              ║");
        printf("\n               ║                                 ║");
        printf("\n               ║  m - print menu                 ║");
        printf("\n               ║  p - print student              ║");
        printf("\n               ║  w - edit student               ║");
        printf("\n               ║  e - exit                       ║");
        printf("\n               ║                                 ║");
        printf("\n               ╚=================================╝");
	printf("\n\n");			
}


