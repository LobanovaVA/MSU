#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int read_matrix(FILE *fp, double *a, int m, int n);
void print_matrix(FILE *fp, double *a, int m, int n);

double norma103(double *a, int m, int n, int i);
double norma106(double *a, int m, int n, int i);
double norma108(double *a, int m, int n, int i);
double norma110(double *a, int m, int n, int i);

void change_strings(double *a, int m, int n, int s1, int s2);
void bubble_down_sort(double *a, int m, int n, double (*norma)(double *a, int m, int n ,int k) );

void mult_Aastr(double *a, int m, int n, double *c, int str);

int main(){
    int m, n, i;
    double *a, *c;
    FILE *in, *out;
    if(!( in=fopen( "input.txt","r"))) return -1;
    if(!(out=fopen("output.txt","w"))) return fclose(in), -1;
    
    if(fscanf(in,"%d%d",&m,&n)!=2)              {    fclose(in); fclose(out); return -1;    }
    if(m<1 || n<2)                                  {    fclose(in); fclose(out); return -1;    }
    if(!(a=(double*)malloc(n*m*sizeof(double)))) {    fclose(in); fclose(out); return -1;    }
    if(!(c=(double*)malloc(m*sizeof(double))))   {    fclose(in); fclose(out); free(a); return -1;    }
    if(!!read_matrix(in, a, m, n)) {    fclose(in); fclose(out); free(a); free(c); return -1;    }
    
//103   bubble_down_sort(a, m, n, norma103);    mult_Aastr(a, m, n, c, m-1);
//106   bubble_down_sort(a, m, n, norma106);    mult_Aastr(a, m, n, c, 0);
//108   bubble_down_sort(a, m, n, norma108);    mult_Aastr(a, m, n, c, m-1);
//110   bubble_down_sort(a, m, n, norma110);    mult_Aastr(a, m, n, c, 0);

    fprintf(out, "%d %d\n", m, n);
    print_matrix(out, a, m, n);
    fprintf(out, "\n");
    print_matrix(out, c, 1, m);
    
    //for(i=0; i<n; i++) printf("i=%d  norm=%lf\n", i, norma108(a,m,n,i));
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
    for (i=0;i<m;i++)
        for (j=0;j<m-i-1;j++)
            if( norma(a,m,n,j)<=norma(a,m,n,j+1) ) change_strings(a,m,n,j,j+1);
}

void change_strings(double *a, int m, int n, int s1, int s2){
    int j;
    double temp, *p1=a+s1*n, *p2=a+s2*n;
    (void) m;
    for(j=0;j<n;j++){  temp=p1[j]; p1[j]=p2[j]; p2[j]=temp;    }
}




double norma103(double *a, int m, int n, int i){
    int j;
    double *p=a+i*n, max=fabs(p[1]-p[0]), r;
    (void) m;
    for(j=2;j<n;j++) {
        r=fabs(p[j]-p[j-1]);
        if(r>max) max=r;
    }
    return max;
}

double norma106(double *a, int m, int n, int i){
    int j;
    double *p=a+i*n, s=0.0;
    (void) m;
    for(j=1;j<n;j++) s+=fabs(p[j]-p[j-1]);
    return s;
}

double norma108(double *a, int m, int n, int i){
    int j;
    double *p=a+i*n, s=0.0;
    (void) m;
    for(j=0;j<n;j++) {
        if(fabs(p[j])<1e-15) return 0;
        else s+=1.0/p[j];
    }
    return (1.0*n)/s;
}

double norma110(double *a, int m, int n, int i){
    int j;
    double *p=a+(i*n), s=0.0, r;
    (void) m;
    for(j=1;j<n;j++) {
        r=p[j]-p[j-1];
        if(r>0) s+=r;
    }
    return s;
}


