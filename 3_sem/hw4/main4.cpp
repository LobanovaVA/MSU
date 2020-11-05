#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>

#include "addition.h"
#include "tree.h"


int main (int argc, char const *argv[])
{
	FILE *fp;
    tree a;
    int  ret;
    if (argc != 2) return printf("Usage: %s (file_name)\n", argv[0]), 4;
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
            case ERROR_NOT_ENOUGH_MEMORY: printf ("Not enough memory for tree %s\n", name); break;
            default: printf ("Unknown error %d in %s\n", ret, name);
		}
		return 3;
	}
    fclose (fp); 

    printf ("\nOriginal tree:\n"); 
    a.print ( a.get_root());
    double t = clock ();
    int ans = 0;
    a.solve_4 (a.get_root(), ans);
    if (!a.is_empty()) printf ("\nAnswer: %d\n", ans);
    t = (clock () - t) / CLOCKS_PER_SEC;
    printf ("\nTime=%f\n", t);
	return 0;
}

