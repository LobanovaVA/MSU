#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>
#define MAX_PRINT 20
#define LEN 1234

int read_array(const char *, char **, int);
void delete_array(char **, int);
void print_array(char **, int);
void merge_arrays(char **, int, char **, int, char**, int (*)(const char *, const char *));
void Neuman_sort(char **, int, char **, int (*)(const char *, const char *));
void ans(char **, int, int (*cmp)(const char *, const char *));

int main(int argc, char **argv){
	int n, ret, i;
    char **a, **b, *name;
    double t;
	if( (argc!=3) || !(n=atoi(argv[1])) )
        return printf("Usage: %s n name\n", argv[0]), 1;
    name=argv[2];
	if(!(a=(char**)malloc(n*sizeof(char*))) )return printf("Not enough memory\n"), 2;
    if(!(b=(char**)malloc(n*sizeof(char*))) )return printf("Not enough memory\n"), 2;
	ret=read_array(name, a, n);
	if(ret<0){
		switch(ret){
            case -1: printf("Cannot open %s\n", name); break;
            case -2: printf("Cannot read %s\n", name); break;
            case -3: printf("Cannot read string in %s\n", name); break;
            default: printf("Unknown error %d in %s\n", ret, name);
		}
        free(a); free(b);
		return 3;
	}
    
    printf("\nOriginal array:\n");  print_array(a, n);
    t=clock();
    Neuman_sort(a, n, b, &strcmp);
    t=clock()-t;
    printf("\nEdited array:\n");  print_array(a, n);
    ans(a,n,strcmp);
    delete_array(a, n);
    delete_array(b, n);
    free(a); free(b);
	printf("Elapsed=%.2f\n", t / CLOCKS_PER_SEC);
	return 0;
}

void merge_arrays(char **a, int n, char **b, int m, char**c, int (*cmp)(const char *, const char *)){
    int i=0, j=0, s=0;
    while(i<n && j<m){
        if(cmp(b[j], a[i])>0) {c[s]=a[i]; i++; s++;}
        else {c[s]=b[j]; j++; s++;}
    }
    while (i<n) {c[s]=a[i]; i++; s++;}
    while (j<m) {c[s]=b[j]; j++; s++;}
}

void Neuman_sort(char **a, int n, char **b, int (*cmp)(const char *, const char *)){
    int d, i, r=0;
    char **c, **a0=a;
    
    for(d=1; d<n; d<<=1){
        for(i=0; (i+2*d)<=n; i+=2*d)
            merge_arrays(a+i, d, a+i+d, d, b+i, cmp);
        merge_arrays(a+i, n-i-r, a+n-r, r, b+i, cmp);
        r=n-i;
        c=a; a=b; b=c;
    }
    if(a!=a0) for(i=0; i<n; i++) b[i]=a[i];
}
int read_array(const char *name, char **a, int n){
	FILE *fp;
	int i, j;
    char buf[LEN];
	if(!(fp=fopen(name, "r"))) return -1;
    for(i=0;i<n;i++){
        if(!fgets(buf, LEN, fp)){
            delete_array(a,i);
            return fclose(fp), -2;
        }
        for(j=0; buf[j]; j++)
            if(buf[j]=='\n') {buf[j]=0; break;}
        if(!(a[i]=(char *)malloc((j+1)*sizeof(char *)))){
            delete_array(a,i);
            return fclose(fp), -3;
        }
        strcpy(a[i], buf);
    }
	fclose(fp);
	return 0;
}
void delete_array(char **a, int n){
    int i;
    for(i=0; i<n; i++) free(a[i]);
}
void print_array(char **a, int n){
	int i=0;
	int m=((n>MAX_PRINT)?MAX_PRINT:n);
	for(; i<m; i++) printf("%s\n", a[i]);
}
void ans(char **a,int n, int (*cmp)(const char *, const char *)){
    int fl=0, i;
    for (i=0; i<n-1; i++){
        if (cmp(a[i],a[i+1])>0) { fl=1; break; }
    }
    if (fl==0) printf("\nOK\n");
    else printf("\nWRONG\n");
}
