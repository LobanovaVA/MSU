#include <stdio.h>
#include <math.h>
#include "h.h"

int main(void){
    double a, b, ret;
    int n;

    printf("Input a, b, n: ");
    if(scanf("%lf %lf %d", &a, &b, &n)!=3) return printf("Usage: number a, b, n OR Invalid number format\n"), 1;

	ret=solve( &f, a, b, n);
    printf("Integral(f(x)dx)=%e\nerror=%e\n", ret, fabs(ret-intf(a, b)) );
    return 0;
}
