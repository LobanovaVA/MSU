#include <stdio.h>
#include "f.h"


int main(int argc, char **argv){
    const char *a, *b, *s;
    int ret;
    if(argc!=4){
        printf("Usage: %s a.txt b.txt strS\n", argv[0]);
        return 1;
    }
    a=argv[1]; b=argv[2]; s=argv[3];
    ret=f(a,b,s);
    if(ret<SUCCESS){
        switch(ret){
            case ERROR_OPEN_A:  printf("Cannot open %s\n", a);  break;
            case ERROR_OPEN_B:  printf("Cannot open %s\n", b);  break;
            case ERROR_READ_A:  printf("Cannot read %s\n", a);  break;
            case ERROR_WRITE_B: printf("Cannot write %s\n",b);  break;
            case ERROR_STR_S:   printf("Incorrect string s\n"); break;
            case ERROR_MEMORY:  printf("Not enough memory\n");  break;
            default: printf("Uknown error %d in either %s or %s\n", ret, a, b);
        }
        return 2;
    }
    printf("Result=%d\n", ret);
    return 0;
}
