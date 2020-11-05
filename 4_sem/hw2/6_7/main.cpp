#include <stdio.h>
#include <time.h>
#include "addition.h"
#include "parser.h"
#include "operation.h"

int main(int argc, char **argv){
    const char *a, *b, *c, *t; char *s; int ret; double time;
    if (argc!=6) return printf("Usage: %s a.txt FILE_1.txt FILE_2.txt strS strT\n", argv[0]), 1;
    a=argv[1]; b=argv[2]; c=argv[3]; s=argv[4]; t=argv[5];


    for (int i=0; s [i]; i++)
        if(s[i]=='\\') { i++; if(s[i]!='_' && s[i]!='\\') return printf("Incorrect strS\n"), ERROR_STR_S; }
    
    operation OP (t, s);
    parser str (OP.get_space_alph (), s);
    time = clock ();
    ret = OP.solve_6 (a, b, &str);
    time = clock () - time;

    if(ret<0)
    {
        switch(ret){
            case ERROR_OPEN_A:  printf("Cannot open %s\n", a);  break;
            case ERROR_OPEN_B:  printf("Cannot open %s\n", b);  break;
            case ERROR_READ_A:  printf("Cannot read %s\n", a);  break;
            case ERROR_WRITE_B: printf("Cannot write %s\n",b);  break;
            default: printf("Uknown error %d in either %s or %s\n", ret, a, b);
        }
    }
    else printf("\nANS_1: %d\nTIME: %lf\n", ret, time/CLOCKS_PER_SEC);

    time = clock ();
    ret = OP.solve_7 (a, c, &str);
    time = clock () - time;

    if(ret<0)
    {
        switch(ret){
            case ERROR_OPEN_A:  printf("Cannot open %s\n", a);  break;
            case ERROR_OPEN_B:  printf("Cannot open %s\n", b);  break;
            case ERROR_READ_A:  printf("Cannot read %s\n", a);  break;
            case ERROR_WRITE_B: printf("Cannot write %s\n",b);  break;
            default: printf("Uknown error %d in either %s or %s\n", ret, a, b);
        }
    }
    else printf("\nANS_7: %d\nTIME: %lf\n\n", ret, time/CLOCKS_PER_SEC);
    return 0;
}





