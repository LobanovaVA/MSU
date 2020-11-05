#include <stdio.h>
#include <string.h>
#include "f.h"
#define LEN 1234

int f(const char *a, const char *b, const char *s, const char *r){
	FILE *in, *out;
	char buf[LEN];
	int c1=0, c2=0, i, lenS=strlen(s);
    char *p1, *p2;
    if(!lenS) return ERROR_STR_S;
	if(!( in=fopen(a, "r"))) return ERROR_OPEN_A;
    if(!(out=fopen(b, "w"))) return fclose(in), ERROR_OPEN_B;

	while(fgets(buf, LEN, in)){
		for(i=0; buf[i]; i++) 
			if(buf[i]=='\n') { buf[i]=0; break; }
        p1=buf; p2=buf; c2=0;
        while(strstr(p1, s)){
            p2=strstr(p1, s);
            c2++;
            *p2=0;
            fprintf(out, "%s%s", p1, r);
            p1=p2+lenS;
            if(ferror(out)){
                fclose(in);
                fclose(out);
                return ERROR_WRITE_B;
            }
        }
        fprintf(out, "%s\n", p1);
        if(ferror(out)){
            fclose(in);
            fclose(out);
            return ERROR_WRITE_B;
        }
        
        if(c2) c1++;
        
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

