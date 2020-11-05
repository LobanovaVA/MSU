#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define N 1<<20

char * strrchr_(const char *, int);
double test(int n, char *(*)(const char *, int), const char *, int);

int main(int argc, char **argv){
    char *str;
    int ch;
    double t_std, t_my;
    if(argc!=3 || strlen(argv[2])>1) return printf("Usage: %s sting char\n", argv[0]), 1;
    str=argv[1];    ch=(int)argv[2][0];

    printf("\nSTD:\n");
    t_std=test(N, strrchr, str, ch);
    printf("Elapsed=%.2f\n", t_std/CLOCKS_PER_SEC);
    printf("\nMYf:\n");
    t_my=test(N, strrchr_, str, ch);
    printf("Elapsed=%.2f\n", t_my/CLOCKS_PER_SEC);
}

char * strrchr_(const char *str, int ch){
    int i=0, p=-1;
    while(str[i]){
        if(str[i]==ch) p=i;
        i++;
    }
    if(str[i]==ch) p=i;
    if(p==-1) return NULL;
    return (char*)(str+p);
}

//char * strrchr_(const char *str, int ch){
//    int i=0;
//    char *p=NULL;
//    while(str[i]){
//        if(str[i]==ch) p=(char*)str+i;
//        i++;
//    }
//    if(str[i]==ch) p=(char*)str+i;
//    return p;
//}

double test(int n, char *(*f)(const char *, int), const char *str, int ch){
    int i; double t;
    char *ans=0;
    t=clock();
    for(i=0; i<n; i++) ans=f(str, ch);
    t=clock()-t;
    printf("Answer: %s\n", ans);
    return t;
}
