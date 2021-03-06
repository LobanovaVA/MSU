#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>
#define MAX_PRINT 20
#define LEN 1234

int read_array(const char *, char **, int);
void delete_array(char **, int);
void print_array(char **, int);
int sort_by_x(char **, int, char *, int (*)(const char *, const char *));
void quick_sort(char **, int, int (*)(const char *, const char *));
void ans(char **, int, int (*cmp)(const char *, const char *));

int main(int argc, char **argv){
	int n, ret;
    char **a, *name;
    double t;
	if( (argc!=3) || !(n=atoi(argv[1])) )
        return printf("Usage: %s n name\n", argv[0]), 1;
    name=argv[2];
	if(!(a=(char**)malloc(n*sizeof(char*))) )return printf("Not enough memory\n"), 2;

	ret=read_array(name, a, n);
	if(ret<0){
		switch(ret){
            case -1: printf("Cannot open %s\n", name); break;
            case -2: printf("Cannot read %s\n", name); break;
            case -3: printf("Cannot read string in %s\n", name); break;
            default: printf("Unknown error %d in %s\n", ret, name);
		}
		free(a);
		return 3;
	}
    printf("\nOriginal array:\n");  print_array(a, n);
    t=clock();
    quick_sort(a, n, &strcmp);
    t=clock()-t;
    printf("\nEdited array:\n");  print_array(a, n);
    ans(a,n,strcmp);
    delete_array(a, n);
    free(a);
	printf("Elapsed=%.2f\n", t / CLOCKS_PER_SEC);
	return 0;
}

void quick_sort(char **a, int n, int (*cmp)(const char *, const char *)){
    char *x;
    int k;
    if(n<2) return;
    while(n>2){
        x=a[n/2];
        k=sort_by_x(a,n,x,cmp);
        if(k<n-k){
            quick_sort(a,k,cmp);
            a+=k;
            n-=k;
        }
        else{   quick_sort(a+k, n-k, cmp); n=k;  }
    }
    if(n==2 && cmp(a[n-2],a[n-1])>0) {x=a[n-2]; a[n-2]=a[n-1]; a[n-1]=x;}
    return;
}

int sort_by_x(char **a, int n, char *x, int (*cmp)(const char *, const char *)){
    int l=0, r=n-1;
    char *f;
    while(r>=l){
        for(; l<n && cmp(x,a[l])>0; l++);
        for(; r>0 && cmp(a[r],x)>0; r--);
        if(l<=r)  {f=a[l]; a[l]=a[r]; a[r]=f; l++; r--;
        }
    }
    return l;
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
