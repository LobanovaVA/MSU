#include<stdio.h>
int f(double* x, int* i, int* j, const char* name);

int main(int argc, char* argv[]){
    char* name;
    int ans, i, j;
    double x;

    if(argc!=2) return printf("Usage: %s Filename\n", argv[0]), 1;
    name=argv[1];
    ans=f(&x, &i, &j, name);
    
    if(ans<0){
        switch(ans){
            case -1: printf("Cannot open %s\n", name); break;
            case -2: printf("Cannot read %s\n", name); break;
            case -3: printf("Empty file %s\n", name);  break;
            default: printf("Unknown error %d in %s\n", ans, name);
        }
        return 1;
    }
    printf("Answer: %i\n", ans);
    printf("Max element: %.16lf\nNumber of the first match with max: %i\nNumber of the last  match with max: %i\n", x, i, j);
    return 0;
}

int f(double* x, int* i, int* j, const char* name){
    FILE* fp;
    double x0;
    int k=1;
    fp=fopen(name, "r");
    if(!fp) return -1;
    if( fscanf(fp, "%lf", &x0)!=1 ) {
      if(feof(fp)) return fclose(fp), -3;
      else return fclose(fp), -2;
    }
    *x=x0; *i=1; *j=1;
    while(fscanf(fp, "%lf", &x0)==1){
        k++;
        if(x0>*x) { *x=x0; *i=k; *j=k; }
        if(!(x0<*x || x0>*x)) *j=k;
    }
    if(!feof(fp)) return fclose(fp), -2;
    fclose(fp);
    return 0;
}
