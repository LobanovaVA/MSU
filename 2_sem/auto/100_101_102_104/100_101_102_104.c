#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int read_matrix(FILE *fp, double *a, int m, int n);
void print_matrix(FILE *fp, double *a, int m, int n);

double norma100(double *a, int m, int n, int i);
double norma101(double *a, int m, int n, int i);
double norma102(double *a, int m, int n, int i);
double norma104(double *a, int m, int n, int i);

void change_strings(double *a, int m, int n, int s1, int s2);
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
    
//100    bubble_up_sort(a, m, n, norma100);    mult_Aastr(a, m, n, c, 0);
//101   bubble_up_sort(a, m, n, norma101);    mult_Aastr(a, m, n, c, 0);
//102   bubble_up_sort(a, m, n, norma102);    mult_Aastr(a, m, n, c, m-1);
//104   bubble_up_sort(a, m, n, norma104);    mult_Aastr(a, m, n, c, m-1);

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
    for (i=0;i<m;i++)
        for (j=0;j<m-i-1;j++)
            if( norma(a,m,n,j)>norma(a,m,n,j+1) ) change_strings(a,m,n,j,j+1);
}

void change_strings(double *a, int m, int n, int s1, int s2){
    int j;
    double temp, *p1=a+s1*n, *p2=a+s2*n;
    (void) m;
    for(j=0;j<n;j++){  temp=p1[j]; p1[j]=p2[j]; p2[j]=temp;    }
}




double norma100(double *a, int m, int n, int i){
    int j;
    double s=0., *p=a+i*n;
    (void) m;
    for(j=0;j<n;j++) s+=fabs(p[j]);
    return s;
}

double norma101(double *a, int m, int n, int i){
    int j;
    double *p=a+i*n, max=p[0];
    (void) m;
    for(j=1;j<n;j++) if(p[j]>max) max=p[j];
    return max;
}

double norma102(double *a, int m, int n, int i){
    int j;
    double s=0., *p=a+i*n;
    (void) m;
    for(j=0;j<n;j++) s+=p[j]*p[j];
    return s;
}

double norma104(double *a, int m, int n, int i){
    int j;
    double *p=a+i*n, max=p[0], min=p[0];
    (void) m;
    for(j=1;j<n;j++) {
        if(p[j]>max) max=p[j];
        if(p[i]<min) min=p[i];
    }
    return max-min;
}
