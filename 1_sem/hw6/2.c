#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_PRINT 20

int read_array(const char *, double *, int);
void print_array(double *, int);
void merge_arrays(double *, int, double *, int, double*, double (*cmp)(double, double));
double comp1(double, double);
double comp2(double, double);

int main(int argc, char *argv[]){
	int n, m, ret;
	char s;
	double *a, *b, *c, t;
    double (*cmp)(double, double);
	char *nameA, *nameB;

	if( (argc!=5) || !(n=atoi(argv[1])) || !(m=atoi(argv[3])) )
		return printf("Usage: %s n m nameA nameB\n", argv[0]), 1;
	a=(double*)malloc(n*sizeof(double));     if(!a) return printf("Not enough memory\n"), 21;
    b=(double*)malloc(m*sizeof(double));     if(!b) return printf("Not enough memory\n"), 22;
    c=(double*)malloc((n+m)*sizeof(double)); if(!c) return printf("Not enough memory\n"), 23;
	nameA=argv[2];  nameB=argv[4];
	ret=read_array(nameA, a, n);
	if(ret<0){
		switch(ret){
            case -1: printf("Cannot open %s\n", nameA); break;
            case -2: printf("Cannot read %s\n", nameA); break;
            default: printf("Unknown error %d in %s\n", ret, nameA);
		}
        free(a); free(b); free(c);
		return 31;
	}
    ret=read_array(nameB, b, m);
    if(ret<0){
        switch(ret){
            case -1: printf("Cannot open %s\n", nameB); break;
            case -2: printf("Cannot read %s\n", nameB); break;
            default: printf("Unknown error %d in %s\n", ret, nameB);
        }
        free(a); free(b); free(c);
        return 32;
    }
    printf("Select sort order (< if Ascending or > if Descending): ");
    if(scanf("%c", &s)!=1 || (s!='<' && s!='>') ) { printf("Incorrect sort order\n"); free(a); free(b); free(c); return 4;}
    if(s=='<') cmp=comp1; if(s=='>') cmp=comp2;
    
    printf("Original array a:\n");	print_array(a, n);
    printf("Original array b:\n");  print_array(b, m);
    t=clock();
    merge_arrays(a, n, b, m, c, cmp);
    t=clock()-t;
    printf("New array c:\n");   print_array(c, n+m);
	printf("Elapsed=%.2f\n", t/CLOCKS_PER_SEC);
	free(a); free(b); free(c);
	return 0;
}

void merge_arrays(double *a, int n, double *b, int m, double *c, double (*cmp)(double, double)){
    int i=0, j=0, s=0;
    while(i<n && j<m){
        if(cmp(b[j], a[i])>0) {c[s]=a[i]; i++; s++;}
        else {c[s]=b[j]; j++; s++;}
    }
    while (i<n) {c[s]=a[i]; i++; s++;}
    while (j<m) {c[s]=b[j]; j++; s++;}
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
double comp1(double a, double b){ return a-b; }
double comp2(double a, double b){ return b-a; }
