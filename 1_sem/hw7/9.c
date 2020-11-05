#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define N 1<<20

size_t strspn_(const char *, const char *);
double test(int, size_t (*)(const char *, const char *), const char *, const char *);

int main(int argc, char **argv){
    char *str1, *str2;
    double t_std, t_my;
    if(argc!=3) return printf("Usage: %s sting1 string2\n", argv[0]), 1;
    str1=argv[1];    str2=argv[2];
    
    printf("\nSTD:\n");
    t_std=test(N, strspn, str1, str2);
    printf("Elapsed=%.2f\n", t_std/CLOCKS_PER_SEC);
    printf("\nMYf:\n");
    t_my=test(N, strspn_, str1, str2);
    printf("Elapsed=%.2f\n", t_my/CLOCKS_PER_SEC);
}

size_t strspn_(const char *str1, const char *str2){
    int i, j, a[256];
    for(i=0; i<256; i++) a[i]=0;
    for(j=0; str2[j]; j++) a[(unsigned int)str2[j]]=1;
    for(i=0; str1[i]; i++)
        if(!a[(unsigned int)str1[i]]) return i;
    return i;
}

double test(int n, size_t (*f)(const char *, const char *), const char *str1, const char *str2){
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
