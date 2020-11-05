#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_PRINT 20

int read_array(const char *, double *, int);
void print_array(double *, int);
void merge_arrays(double *, int, double *, int, double*, double (*cmp)(double, double));
void Neuman_sort(double *, int, double *, double (*cmp)(double, double));
void ans(double *,int, double (*cmp)(double, double));
double comp1(double, double);
double comp2(double, double);

int main(int argc, char *argv[]){
	int n, ret;
	char s;
	double *a, *b, t;
    double (*cmp)(double, double);
    char *nameA;

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
    printf("Select sort order (< if Ascending or > if Descending): ");
    if(scanf("%c", &s)!=1 || (s!='<' && s!='>') ) { printf("Incorrect sort order\n"); free(a); free(b); return 4;}
    if(s=='<') cmp=comp1; if(s=='>') cmp=comp2;
    
    printf("Original array a:\n");	print_array(a,n);
    t=clock();
    Neuman_sort(a, n, b, cmp);
    t=clock()-t;
    printf("Edited array a:\n");   print_array(a,n);
	printf("Elapsed=%.2f\n", t/CLOCKS_PER_SEC);
    ans(a,n,cmp);
	free(a); free(b);
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

void Neuman_sort(double *a, int n, double *b, double (*cmp)(double, double)){
    int d, i, r=0;
    double *c, *a0=a;

    for(d=1; d<n; d<<=1){
        for(i=0; (i+2*d)<=n; i+=2*d)
            merge_arrays(a+i, d, a+i+d, d, b+i, cmp);
        merge_arrays(a+i, n-i-r, a+n-r, r, b+i, cmp);
        r=n-i;
        c=a; a=b; b=c;
    }
    if(a!=a0) for(i=0; i<n; i++) b[i]=a[i];
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
void ans(double *a,int n, double (*cmp)(double, double)){
    int fl=0, i;
    for (i=0; i<n-1; i++){
        if (cmp(a[i],a[i+1])>0) { fl=1; break; }
    }
    if (fl==0) printf("OK\n");
    else printf("WRONG\n");
}
double comp1(double a, double b){ return a-b; }
double comp2(double a, double b){ return b-a; }
