#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int read_matrix(FILE *fp, double *a, int m, int n);
void print_matrix(FILE *fp, double *a, int m, int n);

double norma113(double *a, int m, int n, int j);
double norma116(double *a, int m, int n, int j);
double norma118(double *a, int m, int n, int j);
double norma119(double *a, int m, int n, int j);

void change_columns(double *a, int m, int n, int c1, int c2);
void bubble_down_sort(double *a, int m, int n, double (*norma)(double *a, int m, int n ,int k) );

void mult_Aastr(double *a, int m, int n, double *c, int str);

int main(){
    int m, n, i;
    double *a, *c;
    FILE *in, *out;
    if(!( in=fopen( "input.txt","r"))) return -1;
    if(!(out=fopen("output.txt","w"))) return fclose(in), -1;
    
    if(fscanf(in,"%d%d",&m,&n)!=2)              {    fclose(in); fclose(out); return -1;    }
    if(m<2 || n<1)                                  {    fclose(in); fclose(out); return -1;    }
    if(!(a=(double*)malloc(n*m*sizeof(double)))) {    fclose(in); fclose(out); return -1;    }
    if(!(c=(double*)malloc(m*sizeof(double))))   {    fclose(in); fclose(out); free(a); return -1;    }
    if(!!read_matrix(in, a, m, n)) {    fclose(in); fclose(out); free(a); free(c); return -1;    }
    
//113   bubble_down_sort(a, m, n, norma113);    mult_Aastr(a, m, n, c, m-1);
//116   bubble_down_sort(a, m, n, norma116);    mult_Aastr(a, m, n, c, 0);
//118   bubble_down_sort(a, m, n, norma118);    mult_Aastr(a, m, n, c, m-1);
//119   bubble_down_sort(a, m, n, norma119);    mult_Aastr(a, m, n, c, 0);

    fprintf(out, "%d %d\n", m, n);
    print_matrix(out, a, m, n);
    fprintf(out, "\n");
    print_matrix(out, c, 1, m);

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

void bubble_down_sort(double *a, int m, int n, double (*norma)(double *a, int m, int n ,int k) ){
    int i, j;
    for (i=0;i<n;i++)
        for (j=0;j<n-i-1;j++)
            if( norma(a,m,n,j)<norma(a,m,n,j+1) ) change_columns(a,m,n,j,j+1);
}

void change_columns(double *a, int m, int n, int c1, int c2){
    int i;
    double temp, *p1=a+c1, *p2=a+c2;
    for(i=0;i<m*n;i+=n){  temp=p1[i]; p1[i]=p2[i]; p2[i]=temp;    }
}




double norma113(double *a, int m, int n, int j){
    int i;
    double *p=a+j, max=fabs(p[n]-p[0]), r;
    for(i=2*n;i<m*n;i+=n) {
        r=fabs(p[i]-p[i-n]);
        if(r>max) max=r;
    }
    return max;
}

double norma116(double *a, int m, int n, int j){
    int i;
    double *p=a+j, s=0.0;
    for(i=n;i<m*n;i+=n) s+=fabs(p[i]-p[i-n]);
    return s;
}

double norma118(double *a, int m, int n, int j){
    int i;
    double *p=a+j, s=0.0;
    for(i=0;i<m*n;i++) {
        if(fabs(p[i])<1e-15) return 0;
        else s+=1.0/p[i];
    }
    return (1.0*m)/s;
}

double norma119(double *a, int m, int n, int j){
    int i;
    double *p=a+j, s=0.0, r;
    for(i=n;i<m*n;i+=n) {
        r=p[i]-p[i-n];
        if(r>0) s+=r;
    }
    return s;
}


