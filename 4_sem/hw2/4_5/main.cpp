#include <stdio.h>
#include <time.h>
#include "addition.h"
#include "parser.h"
#include "operation.h"

int main(int argc, char **argv){
    const char *a, *b, *c, *t, *x; char *s; int ret; double time;
    if (argc!=7) return printf("Usage: %s a.txt FILE_1.txt FILE_2.txt strS strT strX\n", argv[0]), 1;
    a=argv[1]; b=argv[2]; c=argv[3]; s=argv[4]; t=argv[5]; x=argv[6];

    if ( strcmp(x,"=") && strcmp(x,"<") && strcmp(x,">") && strcmp(x,"<>") && strcmp(x,"<=") && strcmp(x,">=") )
        return printf("Incorrect strX %s\n", argv[6]), 1;

    operation OP (t, s, x);
    parser str (OP.get_space_alph (), s);

    time = clock ();
    ret = OP.solve_4 (a, b, &str);
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
    else printf("\nANS_4: %d\nTIME: %lf\n", ret, time/CLOCKS_PER_SEC);

    time = clock();
    ret = OP.solve_5 (a, c, &str);
    time = clock() -time;

    if(ret<0)
    {
        switch(ret){
            case ERROR_OPEN_A:  printf("Cannot open %s\n", a);  break;
            case ERROR_OPEN_B:  printf("Cannot open %s\n", b);  break;
            case ERROR_READ_A:  printf("Cannot read %s\n", a);  break;
            case ERROR_WRITE_B: printf("Cannot write %s\n",b);  break;
            default: printf("Uknown error %d in either %s or %s\n", ret, a, c);
        }
    }
    else printf("\nANS_5: %d\nTIME: %lf\n\n", ret, time/CLOCKS_PER_SEC);


    return 0;
}





