#include<stdio.h>
int f(double x, int* i, int* j, const char* name);

int main(int argc, char* argv[]){
    unsigned char end;
    char* name;
    int ans, i, j;
    double x;
    
    if(argc!=2) return printf("Usage: %s Filename\n", argv[0]), 1;
    printf("Input number ");
    if(scanf("%lf%c", &x, &end) != 2 || end!=10) return printf("ERROR invalid number format or value\n"), 1;
    
    name=argv[1];
    ans=f(x, &i, &j, name);
    
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
    if(ans) printf("Number of the first match with input number: %i\nNumber of the last  match with input number: %i\n", i, j);
    return 0;
}

int f(double x, int* i, int* j, const char* name){
    FILE* fp;
    double x0;
    int k=0;
    fp=fopen(name, "r");
    if(!fp) return -1;
    *i=0;
    while(fscanf(fp, "%lf", &x0)==1){
        k++;
        if(!(x0>x || x0<x)) {
            if(!*i) *i=k;
            *j=k;
        }
    }
    if(!feof(fp)) return fclose(fp), -2;
    fclose(fp);
    if(k==0) return -3;
    if(*i==0) return 0;
    else return 1;
}
