#include<stdio.h>
int f(const char* nameA, const char* nameB);

int main(int argc, char * argv[]){
    char* nameA;
    char* nameB;
    int ans;
    if(argc!=3){
	printf("Usage: %s Filename\n", argv[0]);
	   return 1;
	}
    nameA=argv[1];
    nameB=argv[2];

    ans=f(nameA, nameB);
    if(ans<0){
        switch(ans){
            case -11: printf("Cannot open %s\n", nameA); break;
            case -12: printf("Cannot open %s\n", nameB); break;
            case -21: printf("Cannot read %s\n", nameA); break;
	    case -22: printf("Cannot read %s\n", nameB); break;	
            case -31: printf("Empty file %s\n", nameA);  break;
            case -32: printf("Empty file %s\n", nameB);  break;
	    case -33: printf("Empty files %s and %s\n", nameA, nameB);  break;
            default: printf("Unknown error %d\n", ans);
        }
        return 1;
    }
    printf("Answer: %i\n", ans);
    return 0;
}

int f(const char* nameA, const char* nameB){
    FILE* fpA;
    FILE* fpB;
    double a0, a1, a2, b0, b1;
    int k=1;
    fpA=fopen(nameA, "r");
    fpB=fopen(nameB, "r");
    if(!fpA) return -11;
    if(!fpB) return -12;
    if(fscanf(fpA, "%lf", &a0)!=1) {
      if(fscanf(fpB, "%lf", &b0)!=1) { fclose(fpA); fclose(fpB); return -33;}
      fclose(fpA); fclose(fpB); return -31;   }
    if(fscanf(fpB, "%lf", &b0)!=1) {
        fclose(fpA); fclose(fpB); return -32;   }
        
    fscanf(fpB, "%lf", &b1);
    fscanf(fpA, "%lf", &a1);
    b0=b1;
    
    while( fscanf(fpA, "%lf", &a2)==1 && fscanf(fpB, "%lf", &b1)==1 ){
        if( b0*2.0>a0+a2 || b0*2.0<a0+a2 ) k=0;
        b0=b1; a0=a1; a1=a2;
    }
    if(feof(fpA) && !feof(fpB)) {
        k=0;
         while (fscanf(fpB, "%lf", &b1)==1);
    }
    if(!feof(fpA) && feof(fpB)) while (fscanf(fpA, "%lf", &a2)==1);
    
    if(!feof(fpA)){
        fclose(fpA); return -21;    }
    if(!feof(fpB)){
        fclose(fpB); return -22;    }
    fclose(fpA);
    fclose(fpB);    
    return k;
}
