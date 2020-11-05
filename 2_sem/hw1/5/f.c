#include <stdio.h>
#include <string.h>
#include "f.h"
#define LEN 1234

int f(const char *a, const char *b, const char *s, char * (*edit)(char *sp, int *fl)){
	FILE *in, *out;
    char buf[LEN], sp[LEN];
	int count=0, fl=0, flstr=0, i;

	if(!( in=fopen(a, "r"))) return ERROR_OPEN_A;
	if(!(out=fopen(b, "w"))) return fclose(in), ERROR_OPEN_B;
    if((unsigned int)s[0]==94) flstr=1;
    strcpy(sp, s);
    edit(sp,&fl);
    
    if(fl==1) {
        fclose(in);
        fclose(out);
        return ERROR_STR_S;
    }
    if(!strlen(sp)) {
        fclose(in);
        fclose(out);
        return EMPTY_STR_S;
    }
    
	while(fgets(buf, LEN, in)){
		for(i=0; buf[i]; i++) 
			if(buf[i]=='\n') { buf[i]=0; break; }
        
        if( (flstr && strstr(buf, sp+1)==buf) || (!flstr && !!strstr(buf, sp)) ){
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

