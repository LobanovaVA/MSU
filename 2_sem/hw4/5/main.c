#include <stdio.h>
#include <math.h>
#include "h.h"

int main(void){
    double a, b, e, x;
    int ret;

    printf("Input a, b, e: ");
    if(scanf("%lf %lf %lf", &a, &b, &e)!=3) return printf("Usage: number a, b, x OR Invalid number format\n"), 1;

	ret=solve( &f, a, b, e, &x);

	if(ret<0){
        switch(ret){
            case -1: printf("Root is not found\n");  break;
            default: printf("Uknown error %d", ret);
        }
        return 2;
    }

    printf("X=%lf\nIt(solve)=%d\nIt(f)=%d\n", x, ret, get_count());
    printf("f(X)=%.e\n", f(x));
    return 0;
}
