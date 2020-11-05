#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "h.h"

int main(int argc, char **argv){
	const char *nameA=0, *nameB=0;
	int m, n, k, ret;
	double t, *a, *b, *c;
	if( !((argc==4 || argc==5 || argc==6) && (m=atoi(argv[1])) && (n=atoi(argv[2])) && (k=atoi(argv[3])) ))
		return printf("Usage: %s m n i j (fileA.txt) (fileB.txt)\n", argv[0]), 1;
	if(argc>=5) nameA=argv[4];	
	if(argc==6) nameB=argv[5];	
	if(!(a=(double*)malloc((n*m*sizeof(double)))) || !(b=(double*)malloc((n*k*sizeof(double)))) || !(c=(double*)malloc((m*k*sizeof(double)))) )	
		return printf("No enough memory\n"), 2;

	if(nameA){
		ret=read_matrix(a, m, n, nameA);
		if(ret<0){
			switch(ret){
				case ERROR_OPEN_FILE:  printf("Cannot open %s\n", nameA); break;
				case ERROR_READ_FILE:  printf("Cannot read %s\n", nameA); break;
				default: printf("Uknown error %d in %s\n", ret, nameA);
			}
		free(a); free(b); free(c);
		return 3;
		}
	}
	else init_matrix(a, m, n, &fa);

	if(nameB){
		ret=read_matrix(b, n, k, nameB);
		if(ret<0){
			switch(ret){
				case ERROR_OPEN_FILE:  printf("Cannot open %s\n", nameB); break;
				case ERROR_READ_FILE:  printf("Cannot read %s\n", nameB); break;
				default: printf("Uknown error %d in %s\n", ret, nameB);
			}
		free(a); free(b); free(c);
		return 4;
		}
	}
	else init_matrix(b, n, k, &fb);


	
	printf("\nMatrix A:\n");  print_matrix(a, m, n);
	printf("\nMatrix B:\n");  print_matrix(b, n, k);
	t=clock();
	solve(a, b, c, m, n, k);
	t=clock()-t;
	printf("\nMatrix C:\n");  print_matrix(c, m, k);
 	printf("\nTime: %lf\n",  t/CLOCKS_PER_SEC);
	free(a); free(b); free(c);
	return 0;
}