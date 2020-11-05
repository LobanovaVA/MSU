#include<stdio.h>
int f(const char* name);

int main(int argc, char * argv[]){
	char* name;
	int ans;
	if(argc!=2){
	  printf("Usage: %s Filename\n", argv[0]);
	   return 1;
	}
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
    int k=1;
    double x, MAX;
    fp=fopen(name, "r");
    if(!fp) return -1;
    if( fscanf(fp, "%lf", &MAX)!=1 ) {
        fclose(fp);
        return -3;
    }
    while(fscanf(fp, "%lf", &x)==1){
        if(MAX<x) {
            k=0;
            MAX=x;
        }
        if(!(MAX>x)) k++;
    }
    if(!feof(fp)){
        fclose(fp);
        return -2;
    }
    fclose(fp);
    return k;
}