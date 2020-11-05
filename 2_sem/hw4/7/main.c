#include <stdio.h>
#include <math.h>
#include "h.h"

int main(void){
    double e, x0, x;
    int ret;

    printf("Input x0, e: ");
    if(scanf("%lf %lf", &x0, &e)!=2) return printf("Usage: number x0, e OR Invalid number format\n"), 1;

	ret=solve( &f, x0, e, &x);

	if(ret<0){
        switch(ret){
            case -1: printf("Root is not found\n");  break;
            default: printf("Uknown error %d", ret);
        }
        return 2;
    }

   
    printf("X=%.16lf\nIt(solve)=%d\nIt(f)=%d\n", x, ret, get_count());
    printf("f(X)=%.e\n", f(x)-x);
    return 0;
}
