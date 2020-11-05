#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define N 1<<30

char * strstr_(const char *, const char *);
double test(int, char * (*)(const char *, const char *), const char *, const char *);

int main(int argc, char **argv){
    char *str1, *str2;
    double t_std, t_my;
    if(argc!=3) return printf("Usage: %s sting1 string2\n", argv[0]), 1;
    str1=argv[1];    str2=argv[2];
    
    printf("\nSTD:\n");
    t_std=test(N, strstr, str1, str2);
    printf("Elapsed=%.2f\n", t_std/CLOCKS_PER_SEC);
    printf("\nMYf:\n");
    t_my=test(N, strstr_, str1, str2);
    printf("Elapsed=%.2f\n", t_my/CLOCKS_PER_SEC);
}

char * strstr_(const char *str1, const char *str2){
    int i, j=0, p;
    int len1=strlen(str1), len2=strlen(str2);
    if(len2>len1) return NULL;
    
    for(i=0; i<len1-len2+j+1; i++){
        if(str1[i]==str2[j]){   if(j==0) p=i; j++;  }
        else if(j!=0) { i--; j=0;  }
        if (j==len2) return (char*)(str1+p);
    }
    return NULL;
}

double test(int n, char * (*f)(const char *, const char *), const char *str1, const char *str2){
    int i;
    char * ans;
    double t;
    t=clock();
    for(i=0; i<n; i++) ans=f(str1, str2);
    t=clock()-t;
    printf("Answer: %s\n", ans);
    return t;
}
