#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int read_matrix(FILE *fp, double *a, int m, int n);
void print_matrix(FILE *fp, double *a, int m, int n);
void solve10(double *a, int m, int n);

int main(){
    int m, n;
    double *a, *c;
    FILE *in, *out;
    if(!( in=fopen( "input.txt","r"))) return -1;
    if(!(out=fopen("output.txt","w"))) return fclose(in), -1;
    
    if(fscanf(in,"%d%d",&m,&n)!=2)               {    fclose(in); fclose(out); return -1;    }
    if(m<1 || n<1)                               {    fclose(in); fclose(out); return -1;    }
    if(!(a=(double*)malloc(n*m*sizeof(double)))) {    fclose(in); fclose(out); return -1;    }
    if(!!read_matrix(in, a, m, n)) {    fclose(in); fclose(out); free(a); return -1;    }
    

    solve10(a,m,n);
    print_matrix(out, a, m, n);
    fclose(in); fclose(out);
    free(a); free(c);
    return 0;
}



int read_matrix(FILE *fp, double *a, int m, int n){
    int i;
    for(i=0;i<m*n;i++) if(fscanf(fp,"%lf",a+i)!=1) return -1;
    return 0;
}
void print_matrix(FILE *fp, double *a, int m, int n){
    int i, j;
    for(i=0;i<m;i++){
        for(j=0;j<n;j++)
            fprintf(fp, "%lf ", a[i*n+j]);
        fprintf(fp, "\n");
    }
}
void solve10(double *a, int m, int n){
    int str, i, j;
    double max, *p;
    for(i=0;i<m;i++){
        p=a+(i*n);
        for(j=0;j<n;j++) 
            if(p[j]>max) { max=p[j]; str=i; }
    }
    for(i=str*n; i<m*n-n; i++) a[i]=a[i+n];
    p=a+(m*n-n);
    for(j=0;j<n;j++) p[j]=0;


}