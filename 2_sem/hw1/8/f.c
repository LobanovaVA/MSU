#include <stdio.h>
#include <string.h>
#include "f.h"
#define LEN 1234

int f(const char *a, const char *b, const char *s, const char *r, char * (*edit)(char *buf, int *alf, const char *r, int *c2)){
	FILE *in, *out;
    char buf[LEN];
    int c1=0, i, c2=0, alf[256];

    if(!strlen(s)) return ERROR_STR_S;
	if(!( in=fopen(a, "r"))) return ERROR_OPEN_A;
	if(!(out=fopen(b, "w"))) return fclose(in), ERROR_OPEN_B;
    
    for(i=0; i<256; i++) alf[i]=0;
    for(i=0; s[i]; i++) alf[(unsigned int)s[i]]=i+1;
    
	while(fgets(buf, LEN, in)){
		for(i=0; buf[i]; i++) 
			if(buf[i]=='\n') { buf[i]=0; break; }

        edit(buf, alf, r, &c2);
        c1+=c2;
        fprintf(out, "%s\n", buf);
        if(ferror(out)){
            fclose(in);
            fclose(out);
            return ERROR_WRITE_B;
        }
    }
    if(ferror(in)){
        fclose(in);
        fclose(out);
        return ERROR_READ_A;
    }
    fclose(in);
    fclose(out);
    return c1;
}

