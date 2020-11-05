#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_PRINT 20

int read_array(const char *, double *, int);
void print_array(double *, int);
void heap_sort(double *, int);
void max_tree(double *, int, int);
void ans(double *,int );

int main(int argc, char *argv[]){
	int n, ret;
	double *a, t;
    char *nameA;
	if( (argc!=3) || !(n=atoi(argv[1])) )
		return printf("Usage: %s n nameA\n", argv[0]), 1;
	a=(double*)malloc(n*sizeof(double));     if(!a) return printf("Not enough memory\n"), 2;
	nameA=argv[2];
	ret=read_array(nameA, a, n);
	if(ret<0){
		switch(ret){
            case -1: printf("Cannot open %s\n", nameA); break;
            case -2: printf("Cannot read %s\n", nameA); break;
            default: printf("Unknown error %d in %s\n", ret, nameA);
		}
        free(a);
		return 3;
	}
    
    printf("Original array a:\n");	print_array(a,n);
    t=clock();
    heap_sort(a, n);
    t=clock()-t;
    printf("Edited array a:\n");   print_array(a,n);
	printf("Elapsed=%.2f\n", t/CLOCKS_PER_SEC);
    ans(a,n);
    free(a);
	return 0;
}

void heap_sort(double *a, int n){
    int i;  double f;
    max_tree(a, n, i);
    for(i=n/2-1; i>=0; i--) max_tree(a, n, i);

    for(i=n-1; i>=0; i--){
        f=a[i]; a[i]=a[0]; a[0]=f;
        max_tree(a, i, 0);
    }
}

//void max_tree(double *a, int n, int j){
//    int z, mc;  double f;
//    while(2*j+1<n){
//        mc=2*j+1;
//        if(2*j+2<n && a[2*j+2]>a[mc]) mc=2*j+2;
//
//        if(a[mc]>a[j]) {f=a[j]; a[j]=a[mc]; a[mc]=f;}
//        else break;
//        j=mc;
//    }
//}

void max_tree(double *a, int n, int j){
    int z, mc;  double f;
    for(;;){
        mc=j;
        if(2*j+1<n) mc=2*j+1;
        if(2*j+2<n && a[2*j+2]>a[mc]) mc=2*j+2;

        if(a[mc]>a[j]) {f=a[j]; a[j]=a[mc]; a[mc]=f;}
        else break;
        j=mc;
    }
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
void ans(double *a,int n){
    int fl=0, i;
    for (i=0; i<n-1; i++){
        if (a[i]>a[i+1]){ fl=1; break; }
    }
    if (fl==0) printf("OK\n");
    else printf("WRONG\n");
}
