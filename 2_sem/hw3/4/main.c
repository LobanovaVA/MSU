#include <stdio.h>
#include <stdlib.h>
#include "f.h"

int main(int argc, char **argv){
    const char *a;
	int ret, n;
	double x0;
	double *x, *y, *d;

	if(argc!=3 || !(n=atoi(argv[1]) ) )	return printf("Usage: %s n a.txt\n", argv[0]), 1;
    a=argv[2];

    printf("Input number x0: ");
    if(scanf("%lf", &x0)!=1) return printf("Invalid number format\n"), 2;

	x=(double*)malloc(n*sizeof(double));	if(!x) return printf("Not enough memory\n"), 3;
	y=(double*)malloc(n*sizeof(double));	if(!y) return printf("Not enough memory\n"), 4;
    d=(double*)malloc(n*sizeof(double));    if(!d) return printf("Not enough memory\n"), 5;
    

	ret=read_array(n, a, x, y, d);
	if(ret<SUCCESS){
		switch(ret){
          	case ERROR_OPEN: printf("Cannot open %s\n", a); break;
           	case ERROR_READ: printf("Cannot read %s\n", a); break;
            default: printf("Unknown error %d in %s\n", ret, a);
		}
        free(x); free(y); free(d);
		return 6;
	}

	printf("Result=%.16lf\n", f(n, x0, x, y, d));
    free(x); free(y); free(d);
	return 0;
}
