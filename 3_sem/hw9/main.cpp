#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <ncurses.h>

#include "addition.h"
#include "queue.h"

int main (int argc, char const *argv[])
{
    int n1 = 0, n2 = 0, n3 = 0;

    if ( !(argc == 5 && (n1 = atoi (argv[2])) && (n2 = atoi (argv[3])) && (n3 = atoi (argv[4]))) ) 
        return printf("Usage: %s (file_name) (n1>0) (n2>0) (n3>0)\n", argv[0]), 4;
    const char *name = argv[1];

    FILE *fp;
	if (!(fp=fopen(name, "r"))) return printf ("Cannot open input file %s\n", name), ERROR_CANNOT_OPEN_INPUT_FILE;

    queue a;
    int ret = a.read(fp, n1, n2, n3);
    fclose (fp);
    
	if (ret<0) 
	{
		switch (ret)
		{
            case ERROR_CANNOT_OPEN_INPUT_FILE:  printf ("Cannot open input file %s\n", name); break;
            case ERROR_CANNOT_READ_INPUT_FILE:  printf ("Cannot read input file %s\n", name); break;
            case ERROR_CANNOT_READ_CLASS: printf ("Cannot read class in %s\n", name); break;
            case ERROR_CANNOT_INITIALIZE_STUDENT_NAME: printf ("Cannot initialize student name\n"); break;
            case ERROR_NOT_ENOUGH_MEMORY: printf ("Not enough memory to read from %s\n", name); break;
            case ERROR_NOT_ENOUGH_DATA: printf ("Not enough data to read from %s\n", name); break;
            default: printf ("Unknown error %d in %s\n", ret, name);
		}
		return 3;
	}
    resizecons(80*7);
    printf("\n    🐙 🐢 🐤 🐦 🐨 🐩 🐫 🐬 🐯 🐰 🐲 🐳 🐴 🐶 🐷 🐸 🐹 🐺 🐻 🐼\n");
    printf("\n\n                         🌟  HELLO!  🌟\n");
    a.menu ();
    printf("\n\n                        🌛    BYE!   🌛\n\n");
    printf("\n   🐙 🐢 🐤 🐦 🐨 🐩 🐫 🐬  🐯 🐰 🐲 🐳 🐴 🐶 🐷 🐸 🐹 🐺 🐻 🐼\n");
	return 0;
}
