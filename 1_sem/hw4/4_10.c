#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_PRINT 20

int read_array(const char *, double *, int);
void print_array(double *, int);
int reset_equal_x(double *, int, double);
int a_reset_equal_b(double *, int, double *, int);

int main(int argc, char *argv[]){
	int n, m, ret;
	double *a, *b, t;
	char *nameA, *nameB;

	if( (argc!=5) || !(n=atoi(argv[1])) || !(m=atoi(argv[2])) )
		return printf("Usage: %s n m nameA nameB \n", argv[0]), 1;
	a=(double*)malloc(n*sizeof(double));	if(!a) return printf("Not enough memory\n"), 21;
    b=(double*)malloc(m*sizeof(double));    if(!b) return printf("Not enough memory\n"), 22;
	nameA=argv[3];    nameB=argv[4];
	ret=read_array(nameA, a, n);
	if(ret<0){
		switch(ret){
            case -1: printf("Cannot open %s\n", nameA); break;
            case -2: printf("Cannot read %s\n", nameA); break;
            default: printf("Unknown error %d in %s\n", ret, nameA);
		}
		free(a);
		return 31;
	}
    ret=read_array(nameB, b, m);
    if(ret<0){
        switch(ret){
            case -1: printf("Cannot open %s\n", nameB); break;
            case -2: printf("Cannot read %s\n", nameB); break;
            default: printf("Unknown error %d in %s\n", ret, nameB);
        }
        free(a);
        return 32;
    }
    printf("Original array a:\n");  print_array(a, n);
    printf("Original array b:\n");  print_array(b, m);
    t=clock();
    n=a_reset_equal_b(a,n, b, m);
    t=clock()-t;
    printf("Answer: %i\n", n);
    printf("Edited array a:\n");    print_array(a, n);
	printf("Elapsed=%.2f\n", t/CLOCKS_PER_SEC);
	free(a);    free(b);
	return 0;
}

int reset_equal_x(double* a, int n, double x){
    int k=0, i=0;
    for(; i<n; i++){
        if(a[i]<x) k++;
        else a[i-k]=a[i];
    }
    return n-k;
}
int a_reset_equal_b(double *a, int n, double *b, int m){
    int j;
    double x;
    for(j=0; j<m; j++){
        x=b[j];
        n=reset_equal_x(a,n,x);
    }
    return n;
}
int read_array(const char *name, double *a, int n){
	FILE *fp;
	int i=0;
	if(!(fp=fopen(name, "r"))) return -1;
	for(;i<n;i++) if(fscanf(fp,"%lf",(a+i))!=1) return fclose(fp), -2;
    if(!feof(fp)) return fclose(fp), -2;
	fclose(fp);
	return 0;
}
void print_array(double *a, int n){
	int i=0;
	int m=((n>MAX_PRINT)?MAX_PRINT:n);
	for(; i<m; i++) printf("[%d]=%f\n", i, a[i]);
}
