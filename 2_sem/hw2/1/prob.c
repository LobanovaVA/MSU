#include<string.h>
#include<stdio.h>
#include"prob.h"
char * prob(char *s, int *alf){
    int i, j=0;
    char s2[1234];

    if(alf[(unsigned int)s[0]]==0) {
        s2[0]='\\'; s2[1]='<';
        s2[2]=s[0];
        j+=2;
    }
    else s2[0]=s[0];

    for(i=1; s[i]; i++){
        if(alf[(unsigned int)s[i]]==0 && alf[(unsigned int)s[i-1]]==1) {
            s2[j+i]='\\'; s2[j+i+1]='<';
            j+=2;
    	}
        s2[i+j]=s[i];
    }
    s2[i+j]=0;
    strcpy(s,s2);
    //printf("%s\n", s);
    return s;
}



/*
#include<string.h>
#include<stdio.h>
#include"prob.h"

char * prob(char *s, int *alf){
    int i, j = 0;
    char s2[1234];
    strcpy(s2, s);
    
    if(!alf[(unsigned int)s[0]]) {
        strcpy(s2+2, s);
        s2[0]='\\'; s2[1]='<';
        j += 2;
    }

    for(i = 1; s[i]; i++){

        if(!alf[(unsigned int)s[i]] && alf[(unsigned int)s[i-1]]) {
            strcpy(s2+i+j+2, s + i);
            s2[i + j]='\\'; s2[i + j + 1]='<';
            j += 2;
        }
    }
    strcpy(s,s2);
    //printf("%s\n", s);
    return s;
}
*/