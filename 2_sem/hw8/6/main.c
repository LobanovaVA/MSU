#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "h.h"

int main(int argc, char **argv){
	const char *nameA=0, *nameX0=0, *nameB=0;
	int m, n, ret, i;
	double t, tau, *a, *x, *x0, *b, *r;
	if( !((argc==3 || argc==4 || argc==5 || argc==6 ) && (n=atoi(argv[1])) && (m=atoi(argv[2])) ))
		return printf("Usage: %s m n (fileA.txt) (fileX0.txt) (fileB.txt)\n", argv[0]), 1;
	if(argc>=4) nameA=argv[3];	if(argc>=5) nameX0=argv[4]; if(argc==6) nameB=argv[5];
	printf("\nTAU=");
    if(scanf("%lf", &tau)!=1) return printf("Invalid number TAU format\n"), 1;

	if(!( a=(double*)malloc((n*n*sizeof(double)))) ) return printf("No enough memory for A\n"), 2;
	if(!(x0=(double*)malloc((n*sizeof(double)))) ) { free(a); return printf("No enough memory for X0\n"), 2; }
	if(!( x=(double*)malloc((n*sizeof(double)))) ) { free(a); free(x0); return printf("No enough memory for X\n"), 2; }
	if(!( b=(double*)malloc((n*sizeof(double)))) ) { free(a); free(x0); free(x); return printf("No enough memory for B\n"), 2; }
	if(!( r=(double*)malloc((n*sizeof(double)))) ) { free(a); free(x0); free(x); free(b); return printf("No enough memory for R\n"), 2; }

	if(nameA){	if( errors( read_matrix(a, n, n, nameA) , nameA) )	{	free(a); free(x0); free(x); free(b); free(r); return 3;	}}	else init_matrix(a, n, n, &fa);
	if(nameX0){	if( errors( read_matrix(x0,n,1,nameX0) , nameX0) )  {	free(a); free(x0); free(x); free(b); free(r); return 3;	}}	else init_matrix(x0,n,1, &fx0);
	if(nameB){	if( errors( read_matrix(b, n, 1, nameB) , nameB) )	{	free(a); free(x0); free(x); free(b); free(r);return 3;	}}	else init_matrix(b, n, 1, &fb);

	printf("\nMatrix  A:\n"); print_matrix( a, n, n);
	printf("\nVector x0:\n"); print_matrix(x0, n, 1);
	printf("\nVector  b:\n"); print_matrix( b, n, 1);
	m--;
	t=clock();
	solve(a, x0, x, b, r, tau, m, n);
	t=clock()-t;
	printf("\nANSWER...\n");
	printf("\nVector  x:\n"); print_matrix( x, n, 1);
 	printf("\nTime: %lf\n", t/CLOCKS_PER_SEC);
	free(a); free(x0); free(x); free(b); free(r);
	return 0;
}

int errors(int ret, const char *name){
    if(ret<0){
        switch(ret){
			case ERROR_OPEN_FILE:  printf("Cannot open %s\n", name); break;
			case ERROR_READ_FILE:  printf("Cannot read %s\n", name); break;
			default: printf("Uknown error %d in %s\n", ret, name);
        }
        return 1;
    }
    return 0;
}
