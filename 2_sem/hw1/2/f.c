#include <stdio.h>
#include <string.h>
#include "f.h"
#define LEN 1234

int f(const char *a, const char *b, const char *s, const char *t, char * (*prob)(char *sp, int *alf)){
	FILE *in, *out;
    char buf[LEN], bufp[LEN], sp[LEN];
	int count=0, i, alf[256];

	if(!( in=fopen(a, "r"))) return fclose(in), ERROR_OPEN_A;
	if(!(out=fopen(b, "w"))) return ERROR_OPEN_B;
    
    for(i=0; i<256; i++) alf[i]=0;
    for(i=0; t[i]; i++) alf[(unsigned int)t[i]]=1;
    strcpy(sp, s);
    prob(sp,alf);
    if(!strlen(sp)) {
        fclose(in);
        fclose(out);
        return ERROR_STR_S;
    }    
	while(fgets(buf, LEN, in)){
		for(i=0; buf[i]; i++) 
			if(buf[i]=='\n') { buf[i]=0; break; }
        strcpy(bufp, buf);
        prob(bufp, alf);
        
        if(strcmp(bufp, sp)!=0){
            fprintf(out, "%s\n", buf);
            count++;
            if(ferror(out)){
                fclose(in);
                fclose(out);
                return ERROR_WRITE_B;
            }
        }
    }
    if(ferror(in)){
        fclose(in);
        fclose(out);
        return ERROR_READ_A;
    }
    fclose(in);
    fclose(out);
    return count;
}

