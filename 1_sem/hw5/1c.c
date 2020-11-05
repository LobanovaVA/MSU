#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_PRINT 20

int read_array(const char *, double *, int);
void print_array(double *, int);
int location_of_insertion(double *, int, double);
int comp_double(double , double );

int main(int argc, char* argv[]){
	int n, ret;
	double *a, t, x;
	char *name;
	if( (argc!=3) || !(n=atoi(argv[1])) )
        return printf("Usage: %s n name\n", argv[0]), 1;
	a=(double*)malloc(n*sizeof(double));	if(!a) return printf("Not enough memory\n"), 2;
	name=argv[2];
	ret=read_array(name, a, n);
	if(ret<0){
		switch(ret){
            case -1: printf("\e[91m\e[5mCannot open %s\e[0m\n", name); break;
            case -2: printf("\e[91m\e[5mCannot read %s\e[0m\n", name); break;
            default: printf("\e[91m\e[5mUnknown error %d in %s\e[0m\n", ret, name);
		}
		free(a);
		return 3;
	}
    printf("\e[4m\e[36mInput number:\e[0m ");
    if(scanf("%lf", &x)!=1) {
        printf("\e[91m\e[5ERROR invalid number format\e[0m\n");
        free(a);
        return 1;
    }
    printf("\e[4m\e[36mOriginal array:\e[0m\n");  print_array(a, n);
    t=clock();
    printf("\e[4m\e[32mAnswer:\e[0m %i\n", location_of_insertion(a,n,x));
    t=clock()-t;
	printf("\e[4m\e[32mElapsed=\e[0m%.2f\n", t / CLOCKS_PER_SEC);
	free(a);
	return 0;
}

int location_of_insertion(double *a, int n, double x){
    int l=0, r=n-1;
    if(comp_double(x, a[r])==1) return n;
    while(r-l)
        if(comp_double(x, a[(l+r)/2])==1) l=1+(l+r)/2;
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
int comp_double(double a, double  b){
    if(a<b) return -1;
    if(a>b) return  1;
    return 0;
}
