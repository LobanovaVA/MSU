#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_PRINT 20

int read_array(const char *, double *, int);
void print_array(double *, int);
void halfsum_of_neighbors(double *, int);

int main(int argc, char *argv[]){
	int n, ret;
	double *a, t;
	char *name;

	if( (argc!=3) || !(n=atoi(argv[1])) )
		return printf("Usage: %s n name\n", argv[0]), 1;
	a=(double*)malloc(n*sizeof(double));	if(!a) return printf("Not enough memory\n"), 2;
	name=argv[2];
	ret=read_array(name, a, n);
	if(ret<0){
		switch(ret){
            case -1: printf("Cannot open %s\n", name); break;
            case -2: printf("Cannot read %s\n", name); break;
            default: printf("Unknown error %d in %s\n", ret, name);
		}
		free(a);
		return 3;
	}
    printf("Original array:\n");    print_array(a, n);
    t=clock();
    halfsum_of_neighbors(a,n);
    t=clock()-t;
    printf("Edited array:\n");      print_array(a, n);
	printf("Elapsed=%.2f\n", t / CLOCKS_PER_SEC);
	free(a);
	return 0;
}

void halfsum_of_neighbors(double *a, int n){
    int i=1;
    double a0=a[0], a1;
    for(; i<n-1; i++){
        a1=a[i];
        a[i]=(a0+a[i+1])/2;
        a0=a1;
        }
}
int read_array(const char *name, double *a, int n){
	FILE *fp;
	int i=0;
	if(!(fp=fopen(name, "r"))) return -1;
	for(;i<n;i++) if(fscanf(fp, "%lf", (a+i))!=1) return fclose(fp), -2;
    if(!feof(fp)) return fclose(fp), -2;
	fclose(fp);
	return 0;
}
void print_array(double* a, int n){
	int i=0;
	int m=((n>MAX_PRINT)?MAX_PRINT:n);
	for(; i<m; i++)
		printf("[%d] = %f\n", i, a[i]);	
}
