#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int read_matrix(FILE *fp, double *a, int m, int n);
void print_matrix(FILE *fp, double *a, int m, int n);

int cmp115(double *a, int m, int n ,int s1, int s2);
int cmp117(double *a, int m, int n ,int s1, int s2);

void change_columns(double *a, int m, int n, int c1, int c2);
void bubble_up_sort(double *a, int m, int n, int (*cmp)(double *a, int m, int n ,int s1, int s2) );

void mult_Aastr(double *a, int m, int n, double *c, int str);

int main(){
    int m, n, i;
    double *a, *c;
    FILE *in, *out;
    if(!( in=fopen( "input.txt","r"))) return -1;
    if(!(out=fopen("output.txt","w"))) return fclose(in), -1;
    
    if(fscanf(in,"%d%d",&m,&n)!=2)              {    fclose(in); fclose(out); return -1;    }
    if(m<1 || n<1)                                  {    fclose(in); fclose(out); return -1;    }
    if(!(a=(double*)malloc(n*m*sizeof(double)))) {    fclose(in); fclose(out); return -1;    }
    if(!(c=(double*)malloc(m*sizeof(double))))   {    fclose(in); fclose(out); free(a); return -1;    }
    if(!!read_matrix(in, a, m, n)) {    fclose(in); fclose(out); free(a); free(c); return -1;    }
    
//105   bubble_up_sort(a, m, n, cmp105);    mult_Aastr(a, m, n, c, 0);
//107   bubble_up_sort(a, m, n, cmp107);    mult_Aastr(a, m, n, c, 0);
    
    fprintf(out, "%d %d\n", m, n);
    print_matrix(out, a, m, n);
    fprintf(out, "\n");
    print_matrix(out, c, 1, m);
    
    for(i=0; i<n-1; i++) printf("i=%d  cmp107=%d\n", i, cmp107(a,m,n,i,i+1));
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



void mult_Aastr(double *a, int m, int n, double *c, int str){
    int i, j;
    double s, *pai, *pstr=a+(str*n);
    for(i=0;i<m;i++){
        pai=a+i*n; s=0.;
        for(j=0;j<n;j++) s+=pai[j]*pstr[j];
        c[i]=s;
    }
}

void bubble_up_sort(double *a, int m, int n, int (*cmp)(double *a, int m, int n ,int s1, int s2)){
    int i, j;
    for (i=0;i<n;i++)
        for (j=0;j<n-i-1;j++)
            if( cmp(a, m, n, j, j+1) ) change_columns(a,m,n,j,j+1);
}

void change_columns(double *a, int m, int n, int c1, int c2){
    int i;
    double temp, *p1=a+c1, *p2=a+c2;
    for(i=0;i<m*n;i+=n){  temp=p1[i]; p1[i]=p2[i]; p2[i]=temp;    }
}

int cmp115(double *a, int m, int n ,int s1, int s2){
    int i;
    double *p1=a+(s1), *p2=a+(s2);
    for(i=0; i<m*n; i+=n) {
        if(p1[i]-p2[i]>0) return 1;
        if(p1[i]-p2[i]<0) return 0;
    }
    return 1;
}

int cmp117(double *a, int m, int n ,int s1, int s2){
    int i;
    double *p1=a+(s1), *p2=a+(s2), s=0.;
    for(i=0; i<m*n; i+=n) s+=(p1[i]-p2[i]);
    if(s>0) return 1;
    else return 0;
}


