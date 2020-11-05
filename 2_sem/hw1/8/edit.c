#include<string.h>
#include"edit.h"
char * edit(char *buf, int *alf, const char *r, int *c2){
    int i=0, d=0, lenR=strlen(r), p, c=0;
    
    while(buf[i]){
        p=alf[(unsigned int)buf[i]];
        if(p){
            if(p>lenR){ d++; i++; c++; }
            else { buf[i]=r[p-1]; i++; c++;}
        }
        else { buf[i-d]=buf[i]; i++; }

    }
    buf[strlen(buf)-d]=0;
    *c2=c;
    return buf;
}
