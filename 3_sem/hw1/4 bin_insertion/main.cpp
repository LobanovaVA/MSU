#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
 
#include "student.h"
#include "addition.h"
#include "sort.h"

int main (int argc, char const *argv[])
{
    student *a;
    int n;
	if ( !( (argc == 3) && (n = atoi(argv[1]) ) ))
		return printf("Usage: %s n (file_name)\n", argv[0]), 4;

    const char *name = argv[2];
    a = new student[n];
	if (!a) return printf("No enough memmory for alloctaion\n"), 2;
    
    int ret = read_array(name, a, n);
	if (ret<0) 
	{
		switch (ret)
		{
            case ERROR_CANNOT_OPEN_INPUT_FILE:  printf ("Cannot open input file %s\n", name); break;
            case ERROR_CANNOT_READ_INPUT_FILE:  printf ("Cannot read input file %s\n", name); break;
            case ERROR_CANNOT_READ_CLASS: printf ("Cannot read class in %s\n", name); break;
            default: printf ("Unknown error %d in %s\n", ret, name);
		}
		delete []a;
		return 3;
	}

	
	printf ("\nOriginal array:\n");
	print_array (a, n);
    double t = clock();
    bin_insertion_sort(a, n);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("\nEdited array:\n");  
    print_array (a, n);
	printf ("Time=%.2f\n", t);
	if (sort_control(a, n)) printf("OK\n");
    delete []a;
	return 0;
}
