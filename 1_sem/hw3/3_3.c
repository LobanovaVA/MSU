#include<stdio.h>
int f(double x, const char* name);

int main(int argc, char * argv[]){
    unsigned char end;
    char* name;
    int ans;
    double x;
    
    if(argc!=2) return printf("Usage: %s filename\n", argv[0]), 1;
    printf("Input number: ");
    if(scanf("%lf%c", &x, &end) != 2 || end!=10) return printf("ERROR invalid number format or value\n"), 1;
    name=argv[1];
    ans=f(x, name);
    
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
    return 0;
}

int f(double x, const char* name){
    FILE* fp;
    int i=0, f=0;
    double x0;
    fp=fopen(name, "r");
    if(!fp) return -1;
    
    while(fscanf(fp, "%lf", &x0)==1){
        i++;
        if(!(x0>x || x0<x)) {f=i; break;}
    }
    while(fscanf(fp, "%lf", &x0)==1);
    if(!feof(fp)) return fclose(fp), -2; 
    fclose(fp);
    if(i==0) return -3;
    return f;
}
