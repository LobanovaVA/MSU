#include <stdio.h>
#include <math.h>
#include "h.h"

int main(void){
    double x, e, ret;
    
    for(;;){
        printf("Input x: ");
        if(scanf("%lf", &x)!=1 || !(x>0)) return printf("Invalid number format\n"), 1;
        printf("Input eps: ");
        if(scanf("%lf", &e)!=1) return printf("Invalid number format\n"), 2;
        if(!(e>0)) return printf("END\n"), 0;
        //ret=f(x, e, &teilor);
        ret=f(x, e);
        printf("Result=%.16lf\nError=%.16lf\n", ret, fabs(ret-log(x)));
    }
    return 0;
}
