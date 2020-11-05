#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "h.h"

int main(int argc, char **argv){
	const char *nameA=0, *nameX0=0;
	int m, n, ret, i;
	double t, *a, *x, *x0, *r;
	if( !((argc==3 || argc==4 || argc==5 ) && (n=atoi(argv[1])) && (m=atoi(argv[2])) ))
		return printf("Usage: %s m n (fileA.txt) (fileX0.txt)\n", argv[0]), 1;
	if(argc>=4) nameA=argv[3];	if(argc==5) nameX0=argv[4];

	if(!( a=(double*)malloc((n*n*sizeof(double)))) ) return printf("No enough memory for A\n"), 2;
	if(!(x0=(double*)malloc((n*sizeof(double)))) ) { free(a); return printf("No enough memory for X0\n"), 2; }
	if(!( x=(double*)malloc((n*sizeof(double)))) ) { free(a); free(x0); return printf("No enough memory for X\n"), 2; }
    if(!( r=(double*)malloc((n*sizeof(double)))) ) { free(a); free(x0); free(x); return printf("No enough memory for X\n"), 2; }

    if(nameA){
        if( errors( read_matrix(a, n, n, nameA) , nameA) )
        {    free(a); free(x0); free(x);  return 3;    }}
    else init_matrix(a, n, n, &fa);
    
    if(nameX0){
        if( errors( read_matrix(x0, n, 1, nameX0) , nameX0) )
        {    free(a); free(x0); free(x);  return 4;    }}
    else init_matrix(x0, n, 1, &fx0);

	printf("\nMatrix A:\n");   print_matrix(a, n, n);
	printf("\nVector X0:\n");  print_matrix(x0, n, 1);
    m--;
    t=clock();
	solve(a, x0, x, r, m, n);
	t=clock()-t;
 	printf("\nAnswer: %lf\nTime: %lf\n", x[0], t/CLOCKS_PER_SEC);
	free(a); free(x0); free(x);
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
