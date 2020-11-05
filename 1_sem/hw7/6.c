#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define N 1<<20

char * strchr_(const char *, int);
double test(int n, char *(*)(const char *, int), const char *, int);

int main(int argc, char **argv){
    char *str;
    int ch;
    double t_std, t_my;
    if(argc!=3 || strlen(argv[2])>1) return printf("Usage: %s sting char\n", argv[0]), 1;
    str=argv[1];    ch=(int)argv[2][0];

    printf("\nSTD:\n");
    t_std=test(N, strchr, str, ch);
    printf("Elapsed=%.2f\n", t_std/CLOCKS_PER_SEC);
    printf("\nMYf:\n");
    t_my=test(N, strchr_, str, ch);
    printf("Elapsed=%.2f\n", t_my/CLOCKS_PER_SEC);
}

char * strchr_(const char *str, int ch){
    int i=0;
    while(str[i] && str[i]!=ch) i++;
    if(str[i]==0 && ch!=0) return NULL;
    return (char *)(str+i);
}

double test(int n, char *(*f)(const char *, int), const char *str, int ch){
    int i; double t;
    char *ans=0;
    t=clock();
    for(i=0; i<n; i++) ans=f(str, ch);
    t=clock()-t;
    printf("Answer: %s\n", ans);
    return t;
}
