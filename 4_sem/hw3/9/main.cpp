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
    list a, b;
    const char *name;
    int  ret;
    if (argc != 3) return printf("Usage: %s (file_name_for_a) (file_name_for_b)\n", argv[0]), 5;

    name = argv[1];
    if (!(fp=fopen(name, "r"))) return printf ("Cannot open input file for a%s\n", name), ERROR_CANNOT_OPEN_INPUT_FILE;

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

    name = argv[2];
    if (!(fp=fopen(name, "r"))) return printf ("Cannot open input file for b%s\n", name), ERROR_CANNOT_OPEN_INPUT_FILE;

    ret = b.read (fp);    
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
        b.delete_list();
        return 4;
    }
    fclose (fp); 

    printf ("\nOriginal list a:\n");      a.print ();
    printf ("\nOriginal list b:\n");      b.print ();
    double t = clock ();
    if (!a.is_empty() && !b.is_empty()) a.solve_9 (b.get_head()); 
    t = (clock () - t) / CLOCKS_PER_SEC;
    printf ("\nEdited list a:\n");        a.print ();
    printf ("\nTime=%f\n", t);
    a.delete_list ();

    
    return 0;
}
