#include <stdio.h>
#include <string.h>
#include "f.h"
#define LEN 1234

int f(const char *a, const char *b, const char *s, int (*test)(const char *s, const char *buf)){
	FILE *in, *out;
	int i, count=0;
	char buf[LEN];

	if(!( in=fopen(a, "r"))) return ERROR_OPEN_A;
	if(!(out=fopen(b, "w"))) return fclose(in), ERROR_OPEN_B;

	for(i=0; s[i]; i++){
		if((unsigned int)s[i]==92){
			i++;
			if((unsigned int)s[i]!=46 && (unsigned int)s[i]!=92) {
				fclose(in);
				fclose(out);
				return ERROR_STR_S;
			}
		}
	}

	while(fgets(buf, LEN, in)){
		for(i=0; buf[i]; i++) 
			if(buf[i]=='\n') { buf[i]=0; break; }

		if((*test)(s, buf)){
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
