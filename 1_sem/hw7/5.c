#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define N 1<<30

int strcasecmp_(const char *, const char *);
double test(int, int(*)(const char *, const char *), const char *, const char *);

int main(int argc, char **argv){
    char *str1, *str2;
    double t_std, t_my;
    if(argc!=3) return printf("Usage: %s sting1 string2\n", argv[0]), 1;
    str1=argv[1];    str2=argv[2];
    
    printf("\nSTD:\n");
    t_std=test(N, strcasecmp, str1, str2);
    printf("Elapsed=%.2f\n", t_std/CLOCKS_PER_SEC);
    printf("\nMYf:\n");
    t_my=test(N, strcasecmp_, str1, str2);
    printf("Elapsed=%.2f\n", t_my/CLOCKS_PER_SEC);
}

int strcseccmp_(const char *str1, const char *str2){
    int i=0;
    while(str1[i] && (str1[i]==str2[i] || str1[i]-str2[i]!='A'-'a' ) i++;
    return str1[i]-str2[i];
}

double test(int n, int (*f)(const char *, const char *), const char *str1, const char *str2){
    int i, ans;
    double t;
    t=clock();
    for(i=0; i<n; i++){
        ans=f(str1, str2);
    }
    t=clock()-t;
    printf("Answer: %i\n", ans);
    return t;
}
