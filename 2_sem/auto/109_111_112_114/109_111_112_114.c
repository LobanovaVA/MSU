#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int read_matrix(FILE *fp, double *a, int m, int n);
void print_matrix(FILE *fp, double *a, int m, int n);

double norma109(double *a, int m, int n, int j);
double norma111(double *a, int m, int n, int j);
double norma112(double *a, int m, int n, int j);
double norma114(double *a, int m, int n, int j);

void change_columns(double *a, int m, int n, int c1, int c2);
void bubble_up_sort(double *a, int m, int n, double (*norma)(double *a, int m, int n ,int k) );

void mult_Aastr(double *a, int m, int n, double *c, int str);

int main(){
    int m, n;
    double *a, *c;
    FILE *in, *out;
    if(!( in=fopen( "input.txt","r"))) return -1;
    if(!(out=fopen("output.txt","w"))) return fclose(in), -1;
    
    if(fscanf(in,"%d%d",&m,&n)!=2)              {    fclose(in); fclose(out); return -1;    }
    if(m<1 || n<1)                                  {    fclose(in); fclose(out); return -1;    }
    if(!(a=(double*)malloc(n*m*sizeof(double)))) {    fclose(in); fclose(out); return -1;    }
    if(!(c=(double*)malloc(m*sizeof(double))))   {    fclose(in); fclose(out); free(a); return -1;    }
    if(!!read_matrix(in, a, m, n)) {    fclose(in); fclose(out); free(a); free(c); return -1;    }
    
//100   bubble_up_sort(a, m, n, norma109);    mult_Aastr(a, m, n, c, 0);
//101
    bubble_up_sort(a, m, n, norma111);    mult_Aastr(a, m, n, c, 0);
//102   bubble_up_sort(a, m, n, norma112);    mult_Aastr(a, m, n, c, m-1);
//104   bubble_up_sort(a, m, n, norma114);    mult_Aastr(a, m, n, c, m-1);

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

void bubble_up_sort(double *a, int m, int n, double (*norma)(double *a, int m, int n ,int k) ){
    int i, j;
    for (i=0;i<n;i++)
        for (j=0;j<n-i-1;j++)
            if( norma(a,m,n,j)>norma(a,m,n,j+1) ) change_columns(a,m,n,j,j+1);
}

void change_columns(double *a, int m, int n, int c1, int c2){
    int i;
    double temp, *p1=a+c1, *p2=a+c2;
    for(i=0;i<m*n;i+=n){  temp=p1[i]; p1[i]=p2[i]; p2[i]=temp;    }
}




double norma109(double *a, int m, int n, int j){
    int i;
    double s=0., *p=a+j;
    for(i=0;i<n*m;i+=n) s+=fabs(p[j]);
    return s;
}

double norma111(double *a, int m, int n, int j){
    int i;
    double *p=a+j, max=p[0];
    for(i=n;i<m*n;i+=n) if(p[i]>max) max=p[i];
    return max;
}

double norma112(double *a, int m, int n, int j){
    int i;
    double s=0., *p=a+j;
    for(i=0;i<m*n;i+=n) s+=p[i]*p[i];
    return s;
}

double norma114(double *a, int m, int n, int j){
    int i;
    double *p=a+j, max=p[0], min=p[0];
    for(i=n;i<m*n;i+=n) {
        if(p[i]>max) max=p[i];
        if(p[i]<min) min=p[i];
    }
    return max-min;
}
