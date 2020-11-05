#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>

#include "addition.h"
#include "bi_list.h"

bool cmp1 (bi_list_node *x, bi_list_node *y){ return *x < *y; }
bool cmp2 (bi_list_node *x, bi_list_node *y){ return *x > *y; }

int main (int argc, char const *argv[])
{
	FILE *fp;
    bi_list a;
    int  ret, sort_type;
    char sort_oreder;
    bool (*cmp)(bi_list_node*, bi_list_node* );
    //void (*sort)(list a, double (*cmp)(const student&, const student &));

    if (argc != 2) return printf("\nUsage: %s (file_name)\n", argv[0]), 2;
    const char *name = argv[1];
    
    printf("\n< if Ascending\n> if Descending\n\nSelect sort order: ");
    if (scanf ("%c", &sort_oreder) != 1 || (sort_oreder != '<' && sort_oreder != '>'))  return printf("\nIncorrect sort order\n"), 4;
    if (sort_oreder == '<') cmp = cmp1; 
    if (sort_oreder == '>') cmp = cmp2;

    printf ("\n1 - bubble\n2 - min_elem\n3 - max_elem\n4 - linear_insertion\n5 - Neuman\n6 - quick_sort\n\nSelect sort type: ");
    if (scanf ("%d", &sort_type) != 1 || sort_type < 1 || sort_type > 6) return printf("\nIncorrect sort type\n"), 5;

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


    switch (sort_type)
    {
        case 1: a.bubble_sort(cmp); break;
        case 2: a.min_elem_sort(cmp); break;
        case 3: a.max_elem_sort(cmp); break;
        case 4: a.linear_insertion_sort(cmp); break;
        case 5: a.Neuman_sort(cmp); break;
        case 6: a.quick_sort(cmp); break;
        default: { printf ("\nIncorrect sorttype %d/n", sort_type); a.delete_list (); return 5; }
    }

    t = (clock () - t) / CLOCKS_PER_SEC;
    printf ("\nEdited list:\n");        
    a.print ();
    printf ("\nTime=%f\n", t);
    if (a.sort_control(cmp)) printf("OK\n");
    a.delete_list ();
	return 0;
}



/*

    switch (sort_type)
    {
        case 1: sort = bi_list::bubble_sort; break;
        case 2: sort = bi_list::min_elem_sort; break;
        case 3: sort = bi_list::max_elem_sort; break;
        case 4: sort = bi_list::linear_insertion_sort; break;
        case 5: sort = bi_list::Neuman_sort; break;
        case 6: sort = bi_list::quick_sort; break;
        default: printf ("Incorrect sorttype %d", sort_type); return 5;
    }

    */


