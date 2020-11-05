#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define N 1<<30

char * strcpy_(char *, const char *);
double test(int, char *(*f)(char *, const char *), char *, const char *);

int main(int argc, char **argv){
    char *str1, *str2;
    double t_std, t_my;
    
    if(argc!=2) return printf("Usage: %s sting\n", argv[0]), 1;
    str2=argv[1];
    str1=(char*)malloc((strlen(str2)+1)*sizeof(char));
    if(!str1) return printf("Not enough memory\n"), 2;
    
    printf("\nSTD:\n");
    t_std=test(N, strcpy, str1, str2);
    printf("Elapsed=%.2f\n", t_std/CLOCKS_PER_SEC);
    printf("\nMYf:\n");
    t_my=test(N, strcpy_, str1, str2);
    printf("Elapsed=%.2f\n", t_my/CLOCKS_PER_SEC);
    free(str1);
}

char * strcpy_(char *str1, const char *str2){
    int i;
    for(i=0; str2[i]; i++) str1[i]=str2[i];
    str1[i]=0;
    //while( (*(str1++)=*(str2++)) );
    return str1;
}

double test(int n, char *(*f)(char *, const char *), char *str1, const char *str2){
    int i; double t;
    char *ans;
    t=clock();
    for(i=0; i<n; i++) ans=f(str1, str2);
    t=clock()-t;
    printf("Str1=%s\n", ans);
    return t;
}
