#include<stdio.h>
int f(const char* name);

int main(int argc, char * argv[]){
    char* name;
    int ans;
    if(argc!=2) return printf("Usage: %s filename\n", argv[0]), 1;
    name=argv[1];
    ans=f(name);
    
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

int f(const char* name){
    FILE* fp;
    int k=0;
    double x0, x1, x2;
    fp=fopen(name, "r");
    if(!fp) return -1;
    if( fscanf(fp, "%lf", &x0)!=1 ) {
      if(feof(fp)) return fclose(fp), -3;
      else return fclose(fp), -2;
    }
    
    if(fscanf(fp, "%lf", &x1)!=1){
      if(feof(fp)) return fclose(fp), 4;
      else return fclose(fp), -2;
    }
    
    if(fscanf(fp, "%lf", &x2)!=1){
      if(feof(fp)){
	if(!(x0>x1 || x0<x1) ) return fclose(fp), 3;
	else  return fclose(fp), 4;
      }
      else return fclose(fp), -2;
    }
    if(!( x0+x2>2*x1 || x0+x2<2*x1 )) k=1;
    if(!(x0*x2>x1*x1 || x0*x2<x1*x1)) k=2;
    if(!(x0>x1 || x0<x1) && !(x2>x1 || x2<x1)) k=3;
    x0=x1; x1=x2;

   while(fscanf(fp, "%lf", &x2)==1){
        if(k==1 && ( x0+x2>2*x1 || x0+x2<2*x1 )) k=0;
        if(k==2 && (x0*x2>x1*x1 || x0*x2<x1*x1)) k=0;
        if(k==3 && (x2>x1 || x2<x1)) k=0;
        if(k==0) return fclose(fp), k;
        x0=x1; x1=x2;
    }
    
    if(!feof(fp)) return fclose(fp), -2;
    fclose(fp);
    return k;
}
