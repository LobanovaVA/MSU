#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>

#include "addition.h"
#include "list.h"

int main (int argc, char const *argv[])
{
    FILE *fp;
    list a;
    int  ret;

    if (argc != 2) return printf("\nUsage: %s (file_name)\n", argv[0]), 2;
    const char *name = argv[1];
    
    printf("\n< if Ascending\n> if Descending\n\nSelect sort order: ");
    printf ("\nSort type: 6 - quick_sort\n\n");
    
    if (!(fp=fopen(name, "r"))) return printf ("\nCannot open input file %s\n", name), ERROR_CANNOT_OPEN_INPUT_FILE;
    ret = a.read (fp);    
    if (ret<0) 
    {
        switch (ret)
        {
            case ERROR_CANNOT_OPEN_INPUT_FILE:  printf ("\nCannot open input file %s\n", name); break;
            case ERROR_CANNOT_READ_INPUT_FILE:  printf ("\nCannot read input file %s\n", name); break;
            case ERROR_CANNOT_READ_CLASS: printf ("\nCannot read class in %s\n", name); break;
            case ERROR_CANNOT_INITIALIZE_STUDENT_NAME: printf ("\nCannot initialize student name\n"); break;
            case ERROR_NOT_ENOUGH_MEMORY: printf ("\nNot enough memory for list %s\n", name); break;
            default: printf ("\nUnknown error %d in %s\n", ret, name);
        }
        a.delete_list();
        return 3;
    }

    fclose (fp); 
    printf ("\nOriginal list:\n");      
    a.print ();
    double t = clock ();

    student elem;
    elem.init("A", 0);

    a.quick_sort(elem);

    t = (clock () - t) / CLOCKS_PER_SEC;
    printf ("\nEdited list:\n");        
    a.print ();
    printf ("\nTime=%f\n", t);
    if (a.sort_control()) printf("OK\n");
    a.delete_list ();
    return 0;
}

