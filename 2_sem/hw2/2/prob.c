#include<string.h>
#include<stdio.h>
#include"prob.h"
char * prob(char *s, int *alf){
    int i, j=0;
    char s2[1234];

    for(i=0; s[i]; i++){
        s2[i+j]=s[i];
        if(alf[(unsigned int)s[i]]==0 && (!s[i+1] || alf[(unsigned int)s[i+1]]==1)) {
            s2[j+i+1]='\\'; s2[j+i+2]='>';
            j+=2;
    	}
    }

    s2[i+j]=0;
    strcpy(s,s2);
    //printf("%s\n", s);
    return s;
}

