#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "h.h"

int main(int argc, char **argv){
	const char *nameA=0;
	int n, i, ret;
	double t, *a, *buf, *b;
	if( !( (argc==2 || argc==3) && (n=atoi(argv[1])) ) ) return printf("Usage: %s n (fileA.txt)\n", argv[0]), 1;
	if( !( a=(double*)malloc((3*n*n*sizeof(double))) ) ) return printf("No enough memory for A\n"), 2;
	b=a+n*n;	buf=b+n*n;
	if(argc==3) nameA=argv[2];
    if(nameA){	if( errors( read_matrix(a, n, n, nameA) , nameA) )	return free(a), 3;    }
    else init_matrix(a, n, n, &fa);

    memcpy (buf, a, n*n*sizeof(double));
  	bzero(b, n*n*sizeof(double));    for(i=0; i<n*n; i+=n+1) b[i]=1.;

  	printf("\nMatrix A:\n");   print_matrix(a, n, n);
    t=clock();
	ret=solve(buf, b, n);
	t=clock()-t;

	if(ret) { printf("\nBad matrix A\n\nTime: %lf\n\n", t/CLOCKS_PER_SEC); return free(a), 0; }
	printf("\nMatrix A⁻¹:\n");   print_matrix(b, n, n);
	printf("\n\nTime: %lf\n\n", t/CLOCKS_PER_SEC);

	printf("\nDiscrepancy:");
	mult_matrix(a, b, buf, n);	for(i=0;i<n*n;i+=n+1) buf[i]-=1.0;
	printf("\n\n||AA⁻¹-E||");
	printf("\nNorm1=%e", norm1(buf, n));
	printf("\nNorm2=%e", norm2(buf, n));
	printf("\nNorm3=%e", norm3(buf, n));

	mult_matrix(b, a, buf, n);	for(i=0;i<n*n;i+=n+1) buf[i]-=1.0;
	printf("\n\n||A⁻¹A-E||");
	printf("\nNorm1=%e", norm1(buf, n));
	printf("\nNorm2=%e", norm2(buf, n));
	printf("\nNorm3=%e", norm3(buf, n));
	printf("\n\n");
	free(a);
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

