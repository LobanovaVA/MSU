#include<string.h>
#include"edit.h"
char * edit(char *sp, int *fl){
    int i=0, d=0;

    while(sp[i]){
    	if((unsigned int)sp[i]==92){
    		if(sp[i+1] && ( (unsigned int)sp[i+1]==92 || (unsigned int)sp[i+1]==36 ) ) { d++; i++; sp[i-d]=sp[i]; i++; }
    		else { *fl=1; return sp; }
    	}
    	else {sp[i-d]=sp[i]; i++;}
    }
    sp[strlen(sp)-d]=0;
    return sp;
}
