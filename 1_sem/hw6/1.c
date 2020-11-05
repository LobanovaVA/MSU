#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_PRINT 20

int read_array(const char *, double *, int);
void print_array(double *, int);
int location_of_insertion(double *, int, double, double (*cmp)(double, double));
double comp1(double, double);
double comp2(double, double);

int main(int argc, char* argv[]){
	int n, ret;
	char s;
	double *a, t, x;
    double (*cmp)(double, double);
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
    printf("Select sort order (< if Ascending or > if Descending): ");
    if(scanf("%c", &s)!=1 || (s!='<' && s!='>') ) { printf("Incorrect sort order\n"); free(a); return 4;}
    if(s=='<') cmp=comp1; if(s=='>') cmp=comp2;
    
    
    printf("Input number: ");
    if(scanf("%lf", &x)!=1) {
        printf("ERROR invalid number format\n");
        free(a);
        return 1;
    }
    printf("Original array:\n");  print_array(a, n);
    t=clock();
    printf("Answer: %i\n", location_of_insertion(a,n,x,cmp));
    t=clock()-t;
	printf("Elapsed=%.2f\n", t / CLOCKS_PER_SEC);
	free(a);
	return 0;
}

int location_of_insertion(double *a, int n, double x, double (*cmp)(double, double)){
    int l=0, r=n-1;
    if(cmp(x,a[r])>0) return n;
    while(r-l)
        if(cmp(x,a[(l+r)/2])>0) l=1+(l+r)/2;
        else r=(l+r)/2;
    return l;
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
void print_array(double* a, int n){
	int i=0;
	int m=((n>MAX_PRINT)?MAX_PRINT:n);
	for(; i<m; i++) printf("[%d] = %f\n", i, a[i]);
}
double comp1(double a, double b){ return a-b; }
double comp2(double a, double b){ return b-a; }
