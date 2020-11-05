 #include<stdio.h>
#include<math.h>
int f(const char* name, double* d);

int main(int argc, char * argv[]){
    char* name;
    int ans;
    double d;
    if(argc!=2) return printf("Usage: %s filename\n", argv[0]), 1;
    name=argv[1];
    ans=f(name, &d);
    
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
    if(ans!=0) printf("Standard deviation: %.10lf\n", d);
    return 0;
}

int f(const char* name, double* d){
    FILE* fp;
    int k=0;
    double x, s=0, s2=0;
    fp=fopen(name, "r");
    if(!fp) return -1;
    
    while(fscanf(fp, "%lf", &x)==1){
        k++;
        s+=x;
        s2+=x*x;
    }
    if(k==0) {
      if(feof(fp)) return fclose(fp), -3;
      else return fclose(fp), -2;
    }
    
    *d=(s2*k-s*s)/(1.0*k*k);
    if(!feof(fp)) return fclose(fp), -2; 
    fclose(fp);
    return k;
}