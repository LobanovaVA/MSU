#include<string.h>
#include"prob.h"
char * prob(char *sp, int *alf){
    int i=0, d=0;

    while(sp[i]){
    	 if(alf[(unsigned int)sp[i]]==1) { d++; i++; }
    	 else { sp[i-d]=sp[i]; i++; }

    }
    sp[strlen(sp)-d]=0;
    return sp;
}
