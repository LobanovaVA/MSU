#include <stdio.h>
#include <time.h>
#include "addition.h"
#include "parser.h"
#include "operation.h"

int main(int argc, char **argv){
    const char *a, *b, *t; char *s, *r; int ret; double time;
    if (argc!=6) return printf("Usage: %s a.txt FILE_1.txt strS strT strR\n", argv[0]), 1;
    a=argv[1]; b=argv[2]; s=argv[3]; t=argv[4]; r=argv[5];

    operation OP (t, s, r);
    parser str (OP.get_space_alph (), s);
    parser rr (OP.get_space_alph (), r);

    time = clock ();
    ret = OP.solve_3 (a, b, &str, &rr);
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
    else printf("\nANS_3: %d\nTIME: %lf\n", ret, time/CLOCKS_PER_SEC);

    return 0;
}





