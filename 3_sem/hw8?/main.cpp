#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>

#include "addition.h"
#include "v_tree.h"
               
typedef int (v_tree::*func_type) (v_tree_node *, int);

int main (int argc, char const *argv[])
{
	FILE *fp;
    v_tree a;
    int  ret, k = 0;
    if ( !(argc == 3 && ((k = atoi (argv[2])) >= 0) ) ) return printf("Usage: %s (file_name) (k>=0)\n", argv[0]), 4;
    const char *name = argv[1];
	if (!(fp=fopen(name, "r"))) return printf ("Cannot open input file %s\n", name), ERROR_CANNOT_OPEN_INPUT_FILE;

    ret = a.read (fp);
    fclose (fp); 
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
    

    printf ("\nOriginal tree:\n"); 
    a.print ( a.get_root());

    //int (*func[6])(tree_node *, int) = {&solve_1, &solve_2, &solve_3, &solve_4, &solve_5, &solve_6};
    func_type solve[] = {&v_tree::solve_1, &v_tree::solve_2, &v_tree::solve_3, &v_tree::solve_4, &v_tree::solve_5, &v_tree::solve_6};
    
    for (int i = 0; i < 6; i++)
    {
        printf ("\n\nTASK %d\n", i+1);
        double t = clock ();
        if (!a.is_empty()) printf ("Answer: %d\n", (a.*solve[i])(a.get_root(), k));
        t = (clock () - t) / CLOCKS_PER_SEC;
        printf ("Time=%f\n", t);
    }

	return 0;
}





