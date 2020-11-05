#include <stdio.h>
#include <time.h>
#include "addition.h"
#include "record.h"
#include "command.h"
#include "list.h"

void solve(list *a);
int main(int argc, char **argv){

    const char *file = "a.txt";
    if (argc > 2) return printf ("Usage: %s FILE_WITH_COMMANDS.txt FILE_PRINT.txt\n", argv[0]), 1;
    if (argc == 2) file = argv[1];

    FILE *in;
    if (!( in=fopen(file, "r"))) return  printf("Cannot open a.txt\n"), ERROR_OPEN_A;

    list a;
    int ret = a.read(in);
    fclose (in);
    if (ret<0)
    {
        switch (ret)
        {
            case ERROR_OPEN_A:  printf ("Cannot open input file\n"); break;
            case ERROR_READ_A:  printf ("Cannot read input file\n"); break;
            case ERROR_READ_CLASS: printf ("Cannot read record\n"); break;
            case ERROR_NOT_ENOUGH_MEMORY: printf ("Not enough memory to read \n"); break;
            default: printf ("Unknown error %d\n", ret);
        }
        return 3;
    }

    //a.print();
    //command line;


    int alf [256] = {0}; char buf[LEN];
    char spaces_str [7] = {' ', ',', ';', '(', ')', '\t', '\n'};
    for (int i = 0; i < 7; i++) alf[(int)spaces_str[i]] = 1;

    double time = clock ();
    command line;
    while (fgets (buf, LEN, stdin))
    {
        ret = line.parse (alf, buf);
        if (ret < 0) continue;
        ret = a.do_command(line);
        if (ret == 1) break;
    }
 

    time = clock () - time;
    printf("\nTIME: %lf\n\n",time/CLOCKS_PER_SEC);
    return 0;
}














