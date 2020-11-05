#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>

 
#include "student.h"
#include "addition.h"
#include "list.h"
#include "list_node.h"

int solve(list_node *);

int main (int argc, char const *argv[])
{
	FILE *fp;
    list a;
    int  ret;
    if (argc != 2) return printf("Usage: %s n (file_name)\n", argv[0]), 4;

    const char *name = argv[1];
	if (!(fp=fopen(name, "r"))) return printf ("Cannot open input file %s\n", name), ERROR_CANNOT_OPEN_INPUT_FILE;

    ret = a.read (fp);    
	if (ret<0) 
	{
		switch (ret)
		{
            case ERROR_CANNOT_OPEN_INPUT_FILE:  printf ("Cannot open input file %s\n", name); break;
            case ERROR_CANNOT_READ_INPUT_FILE:  printf ("Cannot read input file %s\n", name); break;
            case ERROR_CANNOT_READ_CLASS: printf ("Cannot read class in %s\n", name); break;
            case ERROR_CANNOT_INITIALIZE_STUDENT_NAME: printf ("Cannot initialize student name\n"); break;
            case ERROR_NOT_ENOUGH_MEMORY: printf ("Not enough memory for list %s\n", name); break;
            default: printf ("Unknown error %d in %s\n", ret, name);
		}
		a.delete_list();
		return 3;
	}

    fclose (fp); 
    printf ("\nOriginal list:\n");      a.print ();
    double t = clock ();
    if (!a.is_empty()) a.solve_3 ();
    t = (clock () - t) / CLOCKS_PER_SEC;
    printf ("\nEdited list:\n");        a.print ();
    printf ("\nTime=%f\n", t);
    a.delete_list ();

    
	return 0;
}
