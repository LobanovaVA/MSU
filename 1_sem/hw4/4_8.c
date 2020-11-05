#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_PRINT 20

int read_array(const char *, double *, int);
void print_array(double *, int);
int search_subsequence(const char *, double *, int);

int main(int argc, char *argv[]){
    int n, ret, ans;
    double *a, t;
    char *nameA, *nameF;
    
    if( (argc!=4) || !(n=atoi(argv[2])) )
        return printf("Usage: %s filename n nameA\n", argv[0]), 1;
    a=(double*)malloc(n*sizeof(double));     if(!a) return printf("Not enough memory\n"), 21;
    nameF=argv[1];  nameA=argv[3];
    ret=read_array(nameA, a, n);
    if(ret<0){
        switch(ret){
            case -11: printf("Cannot open %s\n", nameA); break;
            case -21: printf("Cannot read %s\n", nameA); break;
            default: printf("Unknown error %d in %s\n", ret, nameA);
        }
        free(a);
        return 31;
    }
    
    printf("Original array a:\n");  print_array(a, n);
    t=clock();
    ans=search_subsequence(nameF, a, n);
    if(ans<0){
        switch(ans){
            case -12: printf("Cannot open %s\n", nameF); break;
            case -22: printf("Cannot read %s\n", nameF); break;
            case -32: printf("Empty file %s\n", nameF);  break;
            default: printf("Unknown error %d in %s\n", ans, nameF);
        }
        return 1;
    }
    
    t=clock()-t;
    printf("Answer: %i\n", ans);
    printf("Elapsed=%.2f\n", t/CLOCKS_PER_SEC);
    free(a);
    return 0;
}

int search_subsequence(const char *nameF, double *a, int n){
    FILE *fp;
    int ans=0, k=0, i=0;
    double x;
    fp=fopen(nameF, "r");
    if(!fp) return -12;
    
    while(fscanf(fp, "%lf", &x)==1){
        k++;
        if( !(x>a[i] || x<a[i])) i++;
        else i=0;
        if(i==n) {
            i=0; ans++;
        }
    }
    if(k==0 && feof(fp)) return fclose(fp), -32;
    if(!feof(fp)) return fclose(fp), -22;
    fclose(fp);
    return ans;
}
int read_array(const char *name, double *a, int n){
    FILE *fp;
    int i=0;
    if(!(fp=fopen(name, "r"))) return -11;
    for(;i<n;i++) if(fscanf(fp, "%lf", (a+i))!=1) return fclose(fp), -21;
    if(!feof(fp)) return fclose(fp), -21;
    fclose(fp);
    return 0;
}
void print_array(double *a, int n){
    int i=0;
    int m=((n>MAX_PRINT)?MAX_PRINT:n);
    for(; i<m; i++) printf("[%d]=%f\n", i, a[i]);
}
