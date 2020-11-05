#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "h.h"

int main(int argc, char **argv){
	const char *nameA=0, *nameB=0;
	int m, n, i, ret;
	double t, ans, *a, *b;
	if( !((argc==3 || argc==4 || argc==5 ) && (m=atoi(argv[1])) && (n=atoi(argv[2])) ))
		return printf("Usage: %s m n (fileA.txt) (fileX.txt) (fileB.txt)\n", argv[0]), 1;
	if(argc>=4) nameA=argv[3];	if(argc==5) nameB=argv[4];

	if(!(a=(double*)malloc((n*m*sizeof(double)))) || !(b=(double*)malloc((n*m*sizeof(double)))) )	
		return printf("No enough memory\n"), 2;

	if(nameA){
		ret=read_matrix(a, m, n, nameA);
		if(ret<0){
			switch(ret){
				case ERROR_OPEN_FILE:  printf("Cannot open %s\n", nameA); break;
				case ERROR_READ_FILE:  printf("Cannot read %s\n", nameA); break;
				default: printf("Uknown error %d in %s\n", ret, nameA);
			}
		free(a); free(b);
		return 3;
		}
	}
	else init_matrix(a, m, n, &fa);

	if(nameB){
		ret=read_matrix(b, n, m, nameB);
		if(ret<0){
			switch(ret){
				case ERROR_OPEN_FILE:  printf("Cannot open %s\n", nameB); break;
				case ERROR_READ_FILE:  printf("Cannot read %s\n", nameB); break;
				default: printf("Uknown error %d in %s\n", ret, nameB);
			}
		free(a); free(b); 
		return 4;
		}
	}
	else //init_matrix(b, n, m, &fb);
	{
	  for(i=1; i<n*m; i++) b[i]=0;
	  b[0]=-1.; b[1]=1;
	  b[n*m-2]=1.0;
	  b[n*m-1]=(double)(1-n)/(double)n;
	  for(i=1; i<n-1; i++){
	    b[i*n+i]=-2.0;
	    b[i*n+i-1]=1.0;
	    b[i*n+i+1]=1.0;
	  }
	}


	
	printf("\nMatrix A:\n");  print_matrix(a, m, n);
	printf("\nMatrix B:\n");  print_matrix(b, n, m);
	t=clock();
	ans=solve(a, b, m, n);
	t=clock()-t;
 	printf("\nAnswer: %lf\nTime: %lf\n", ans, t/CLOCKS_PER_SEC);
	free(a); free(b);
	return 0;
}