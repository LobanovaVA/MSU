#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "h.h"

int main(int argc, char **argv){
	const char *name=0;
	int n, ret, ans;
	double t, *a;
	if( !((argc==2 || argc==3) && (n=atoi(argv[1]))  ))
		return printf("Usage: %s m n (file.txt)\n", argv[0]), 1;
	if(argc==3) name=argv[2];	
	if(!(a=(double*)malloc((n*n*sizeof(double)))))	
		return printf("No enough memory\n"), 2;

	if(name){
		ret=read_matrix(a, n, name);
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
	else init_matrix(a, n);
	
	printf("\nOriginal matrix:\n");  print_matrix(a, n);
	t=clock();
	ans=solve(a, n);
	t=clock()-t;
 	printf("\nAnswer: %d\nTime: %lf\n", ans, t/CLOCKS_PER_SEC);
	free(a);
	return 0;
}
