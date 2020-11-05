#include <stdio.h>
#include <string.h>
#include "f.h"
#define LEN 1234

int f(const char *a, const char *b, const char *s, const char *t, char * (*prob)(char *s, int *alf)){
	FILE *in, *out;
    char buf[LEN], bufp[LEN];
	int count=0, i, alf[256];
    //char s2[LEN];

	if(!( in=fopen(a, "r"))) return ERROR_OPEN_A;
	if(!(out=fopen(b, "w"))) return fclose(in), ERROR_OPEN_B;
    
    for(i=0; i<256; i++) alf[i]=0;
    for(i=0; t[i]; i++) alf[(unsigned int)t[i]]=1;

    for(i=0; s[i]; i++){
        if((unsigned int)s[i]!=92 && (unsigned int)s[i]!=62 && alf[(unsigned int)s[i]]==0 && s[i+1] && alf[(unsigned int)s[i+1]]==1) {
            fclose(in);
            fclose(out);
            return ERROR_STR_S;
        }
        if((unsigned int)s[i]==92 && s[i+1] && (unsigned int)s[i+1]==40){
            if(i && i+2<strlen(s)){
                if( alf[(unsigned int)s[i-1]] || !alf[(unsigned int)s[i+2]] ) {
                    fclose(in);
                    fclose(out);
                    return ERROR_STR_S;
                }

            }
        }
    }
    
    //strcpy(s2,s);
    //prob(s2, alf);
	while(fgets(buf, LEN, in)){
		for(i=0; buf[i]; i++) 
			if(buf[i]=='\n') { buf[i]=0; break; }
        strcpy(bufp, buf);
        prob(bufp, alf);
        
        if(!!strstr(bufp, s)){          //s2
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

