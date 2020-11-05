#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_PRINT 20

int read_array(const char *, double *, int);
void print_array(double *, int);
void merge_arrays(double *, int, double *, int, double*);
void Neuman_sort(double *, int, double *);

int main(int argc, char *argv[]){
	int n, m, ret;
	double *a, *b, t;
	char *nameA, *nameB;

	if( (argc!=3) || !(n=atoi(argv[1])) )
		return printf("Usage: %s n nameA\n", argv[0]), 1;
	a=(double*)malloc(n*sizeof(double));     if(!a) return printf("Not enough memory\n"), 21;
    b=(double*)malloc(n*sizeof(double));     if(!b) return printf("Not enough memory\n"), 22;
	nameA=argv[2];
	ret=read_array(nameA, a, n);
	if(ret<0){
		switch(ret){
            case -1: printf("Cannot open %s\n", nameA); break;
            case -2: printf("Cannot read %s\n", nameA); break;
            default: printf("Unknown error %d in %s\n", ret, nameA);
		}
        free(a); free(b);
		return 3;
	}
    
    printf("Original array a:\n");	print_array(a,n);
    t=clock();
    Neuman_sort(a, n, b);
    t=clock()-t;
    printf("Edited array a:\n");   print_array(a,n);
	printf("Elapsed=%.2f\n", t/CLOCKS_PER_SEC);
	free(a); free(b);
	return 0;
}

void merge_arrays(double *a, int n, double *b, int m, double *c){
    int i=0, j=0, s=0;
    while(i<n && j<m){
        if(a[i]<b[j]) {c[s]=a[i]; i++; s++;}
        else {c[s]=b[j]; j++; s++;}
    }
    while (i<n) {c[s]=a[i]; i++; s++;}
    while (j<m) {c[s]=b[j]; j++; s++;}
}

void Neuman_sort(double *a, int n, double *b){
    double c;
    int i;
    if(n<2) return;
    Neuman_sort(a, n/2, b);
    Neuman_sort(a+n/2, n-n/2, b+n/2);
    merge_arrays(a, n/2, a+n/2, n-n/2, b);
    //memcpy(a, b, n*sizeof(double));
    for(i=0; i<n; i++){ c=a[i]; a[i]=b[i]; b[i]=c; }
    
}

int read_array(const char *name, double *a, int n){
	FILE *fp;
	int i=0;
	if(!(fp=fopen(name, "r"))) return -1;
	for(;i<n;i++) if(fscanf(fp, "%lf", (a+i))!=1) return fclose(fp), -2;
    //if(!feof(fp)) return fclose(fp), -2;
	fclose(fp);
	return 0;
}
void print_array(double *a, int n){
	int i=0;
	int m=((n>MAX_PRINT)?MAX_PRINT:n);
	for(; i<m; i++) printf("[%d]=%f\n", i, a[i]);
}
