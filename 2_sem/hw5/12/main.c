#include <stdio.h>
#include <math.h>
#include "h.h"

int main(void){
    double a, b, r, e;
    int ret;

    printf("Input a, b, e: ");
    if(scanf("%lf %lf %lf", &a, &b, &e)!=3) return printf("Usage: number a, b, e OR Invalid number format\n"), 1;

	ret=solve( &x, &y, a, b, e, &r);
		if(ret<0){
        switch(ret){
            case -1: printf("Lenght is not found\n");  break;
            default: printf("Uknown error %d\n", ret);
        }
        return 2;
    }
    printf("Lenght=%e\nerror=%e\nn=%d\n", r, fabs(r-intf(a, b)), ret );
    return 0;
}
