#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "h.h"

int main(int argc, char **argv){
	const char *nameA=0, *nameX=0, *nameB=0;
	int m, n, ret, i, j;
	double t, ans, *a, *b, *x, s;
	if( !((argc==3 || argc==4 || argc==5 || argc==6) && (m=atoi(argv[1])) && (n=atoi(argv[2])) ))
		return printf("Usage: %s m n (fileA.txt) (fileX.txt) (fileB.txt)\n", argv[0]), 1;
	if(argc>=4) nameA=argv[3];		if(argc>=5) nameX=argv[4];		if(argc==6) nameB=argv[5];

	if(!(a=(double*)malloc((n*m*sizeof(double)))) || !(x=(double*)malloc((n*sizeof(double)))) || !(b=(double*)malloc((m*sizeof(double)))) )	
		return printf("No enough memory\n"), 2;

	if(nameA){
		ret=read_matrix(a, m, n, nameA);
		if(ret<0){
			switch(ret){
				case ERROR_OPEN_FILE:  printf("Cannot open %s\n", nameA); break;
				case ERROR_READ_FILE:  printf("Cannot read %s\n", nameA); break;
				default: printf("Uknown error %d in %s\n", ret, nameA);
			}
		free(a); free(b); free(x);
		return 3;
		}
	}
	else init_matrix(a, m, n, &fa);

	if(nameX){
		ret=read_matrix(x, n, 1, nameX);
		if(ret<0){
			switch(ret){
				case ERROR_OPEN_FILE:  printf("Cannot open %s\n", nameX); break;
				case ERROR_READ_FILE:  printf("Cannot read %s\n", nameX); break;
				default: printf("Uknown error %d in %s\n", ret, nameX);
			}
		free(a); free(b); free(x);
		return 4;
		}
	}
	else init_matrix(x, n, 1, &fx);

	if(nameB){
		ret=read_matrix(b, m, 1, nameB);
		if(ret<0){
			switch(ret){
				case ERROR_OPEN_FILE:  printf("Cannot open %s\n", nameB); break;
				case ERROR_READ_FILE:  printf("Cannot read %s\n", nameB); break;
				default: printf("Uknown error %d in %s\n", ret, nameB);
			}
		free(a); free(b); free(x);
		return 5;
		}
	}
	else //init_matrix(b, m, 1, &fb);
	{
	  for(i=0; i<m; i++){
	    s=0;
	    for(j=1; j<n; j+=2) s+=a[i*n+j];
	    b[i]=s;
	  }
	}


	
	printf("\nMatrix A:\n");  print_matrix(a, m, n);
	printf("\nVector X:\n");  print_matrix(x, n, 1);
	printf("\nVector B:\n");  print_matrix(b, m, 1);
	t=clock();
	ans=solve(a, x, b, m, n);
	t=clock()-t;
 	printf("\nAnswer: %lf\nTime: %lf\n", ans, t/CLOCKS_PER_SEC);
	free(a); free(b); free(x);
	return 0;
}