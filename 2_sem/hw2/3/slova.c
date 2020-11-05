#include<string.h>
#include<stdio.h>
#include"slova.h"
void slova(const char *s, int *alf,char **slova_str){
    int i=0, k=0, h;

    while(s[i]){
        if(alf[(unsigned int)s[i]]==0 && ( i==0 || alf[(unsigned int)s[i-1]]==1) ) {
            h=0;
            while(s[i] && alf[(unsigned int)s[i]]==0) {
                slova_str[k][h]=s[i];
                i++; h++;
            }
            slova_str[k][h]=0;
            k++;
        }
        else i++;
    }
    slova_str[k][0]=0;
}


