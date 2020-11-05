#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "h.h"

int read_matrix(double *a, int m, int n, const char *name){
	FILE*fp;
	int i, j;
	if(!(fp=fopen(name, "r"))) return ERROR_OPEN_FILE;
	for(i=0; i<m; i++)
		for(j=0; j<n; j++)
			if(fscanf(fp, "%lf", a+i*n+j)!=1) return fclose(fp), ERROR_READ_FILE; 
	fclose(fp);
	return 0;	
}

void print_matrix(double *a, int m, int n){
	int i, j, str, col;
	str=(m>MAX_PRINT)?MAX_PRINT:m;
	col=(n>MAX_PRINT)?MAX_PRINT:n;
	for(i=0; i<str; i++){
		for(j=0; j<col; j++)
			printf("%18.6lf   ", *(a+i*n+j));
		printf("\n");
	}
}

void  init_matrix(double *a, int m, int n, double(*f)(double, double)){
	int i, j;
	//srand(time(NULL));      
	//for(i=0; i<m*n; i++) *(a+i)=rand();
	for(i=0; i<m; i++) for(j=0; j<n; j++) a[i*n+j]=f((double)i,(double)j);
}

double fa(double i, double j){ return fabs(i-j);}
double fb(double i, double j){
  (void) i;
  if ((int)j%2)  return 1.;
  else return (-1.);
}