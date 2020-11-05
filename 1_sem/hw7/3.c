#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define N 1<<30

char * strcat_(char *, const char *);
double test(int, char *(*)(char *, const char *), char *, const char *);

int main(int argc, char **argv){
    char *str1, *str2, *buf;
    double t_std, t_my;
   
    if(argc!=3) return printf("Usage: %s sting1 string2\n", argv[0]), 1;
    str1=argv[1];
    str2=argv[2];
    buf=(char *)malloc((strlen(str1)+strlen(str2)+1)*sizeof(char));
    if(!buf) return printf("Not enough memory\n"), 2;
    strcpy(buf, str1);
    
    printf("\nSTD:\n");
    t_std=test(N, strcat, buf, str2);
    printf("Elapsed=%.2f\n", t_std/CLOCKS_PER_SEC);
    strcpy(buf, str1);
    printf("\nMYf:\n");
    t_my=test(N, strcat_, buf, str2);
    printf("Elapsed=%.2f\n", t_my/CLOCKS_PER_SEC);
    free(buf);
}

char *strcat_(char *str1, const char *str2){
    int i, len1;
    len1=strlen(str1);
    for(i=0; str2[i]; i++) str1[i+len1]=str2[i];
    str1[i+len1]=0;
    //while( (*((str1+len1)++)=*(str2++)) );
    return str1;
}
/*
char *strcat_ ( char *string1, const char *string2 ){
    return strcpy(str1+strlen(str1), str2);
}
*/
double test(int n, char *(*f)(char *, const char *), char *str1, const char *str2){
    int i, len1;
    double t;
    len1=strlen(str1);
    t=clock();
    for(i=0; i<n; i++){
        str1[len1]=0;
        f(str1, str2);
    }
    t=clock()-t;
    printf("Str1=%s\n", str1);
    return t;
}
