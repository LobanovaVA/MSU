#include <stdio.h>
#include <time.h>
// #include "addition.h"
// #include "record.h"
// #include "command.h"
#include "list.h"

int name_hash (char *str, int n)
{
    int sum = 0;
    for (int i = 0; str[i]; i++)
        sum += (int)str[i];
    return sum%n;
}

int main(int argc, char **argv){

    const char *file; int n;
    if (argc !=3 || !(n = atoi(argv[2])) || n <= 0 ) return printf ("Usage: %s FILE.txt number\n", argv[0]), 1;
    file = argv[1]; n = atoi(argv[2]);

    FILE *in;
    if (!( in=fopen(file, "r"))) return  printf("Cannot open a.txt\n"), ERROR_OPEN_A;
 
    list a;
    hash h(n);

    int ret = a.read(in, h);
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

    //printf("\n\n");
    //a.print();
    //h.print();

    int alf [256] = {0}; char buf[LEN];
    char spaces_str [7] = {' ', ',', ';', '(', ')', '\t', '\n'};
    for (int i = 0; i < 7; i++) alf[(int)spaces_str[i]] = 1;

    double time = clock ();

    command line;
    while (fgets (buf, LEN, stdin))
    {
        ret = line.parse (alf, buf);
        if (ret < 0) continue;
        ret = a.do_command(line, h);
        if (ret == 1) break;
    }
 

    time = clock () - time;
    printf("\nTIME: %lf\n\n",time/CLOCKS_PER_SEC);
    return 0;
}














