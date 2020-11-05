#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "h.h"

int main(int argc, char **argv){
	const char *name=0;
	int n, m, ret;
	double t, *a;
	if( !((argc==3 || argc==4) && (m=atoi(argv[1])) && (n=atoi(argv[2]))  ))
		return printf("Usage: %s m n (file.txt)\n", argv[0]), 1;
	if(argc==4) name=argv[3];	
	if(!(a=(double*)malloc((n*m*sizeof(double)))))	
		return printf("No enough memory\n"), 2;

	if(name){
		ret=read_matrix(a, m, n, name);
		if(ret<0){
			switch(ret){
				case ERROR_OPEN_FILE:  printf("Cannot open %s\n", name); break;
				case ERROR_READ_FILE:  printf("Cannot read %s\n", name); break;
				default: printf("Uknown error %d in %s\n", ret, name);
			}
		free(a);
		return 3;
		}
	}
	else init_matrix(a, m, n, f);
	
	printf("\nOriginal matrix:\n");  print_matrix(a, m, n);
	t=clock();
	solve(a, m, n);
	t=clock()-t;
	printf("\nChanged matrix:\n");  print_matrix(a, m, n);
 	printf("\nTime: %lf\n", t/CLOCKS_PER_SEC);
	free(a);
	return 0;
}
