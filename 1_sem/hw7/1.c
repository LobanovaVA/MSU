#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define N 1<<30

size_t strlen_(const char *);
double test(int n, size_t(*f)(const char *), const char *);

int main(int argc, char **argv){
    char *str;
    double t_std, t_my;
    if(argc!=2) return printf("Usage: %s sting\n", argv[0]), 1;
    str=argv[1];

    printf("\nSTD:\n");
    t_std=test(N, strlen, str);
    printf("Elapsed=%.2f\n", t_std/CLOCKS_PER_SEC);
    printf("\nMYf:\n");
    t_my=test(N, strlen_, str);
    printf("Elapsed=%.2f\n", t_my/CLOCKS_PER_SEC);
}

size_t strlen_(const char *str){
    int i;
    for(i=0; str[i]; i++);
    return i;
}

double test(int n, size_t(*f)(const char *), const char *str){
    int i; double t;
    size_t ans;
    t=clock();
    for(i=0; i<n; i++) ans=f(str);
    t=clock()-t;
    printf("Len=%zu\n", ans);
    return t;
}
