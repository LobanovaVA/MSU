#include <stdio.h>
#include <string.h>
#include "f.h"
#define LEN 1234

int f(const char *a, const char *b, const char *s){


	FILE *in, *out;
    int i, j, count=0, lcount=0, o=0;
    char  buf[LEN];
    char l;
  
	if(!( in=fopen(a, "r"))) return ERROR_OPEN_A;
	if(!(out=fopen(b, "w"))) return fclose(in), ERROR_OPEN_B;


    while (fgets (buf, LEN, in)!=NULL) {
        if (s[0]!='\0') {
            for (i=0, j=0; i<LEN && buf[i]; i++) {
                o = 0;
                if (s[j]=='\\') {	j++; o = 1;		}

                if (s[j]=='\0' && (buf[i]=='\0' || buf[i]=='\n')) {
                    fprintf (out, "%s", buf);
                    count++;
    				if(ferror(out)){
             	 	  	fclose(in);
            	    	fclose(out);
             	   		return ERROR_WRITE_B;
           			}                
                    break;
                }

                if (s[j]!='\0') break;
           
                if (s[j]!='\\' || o!=0) {                    
                    if (s[j+1]!='*') {
                        if (s[j]!=buf[i]) break;
                        j++;
                        continue;
                    }
                    if (s[j + 1]=='*') {
                        lcount=0;
                        l=s[j];
                        while (buf[i]==s[j]) {
                            i++;
                            lcount++;
                        }
                        while (s[j]==l) {
                            if(s[j+1]=='*') {
                                j+=2;
                                if(s[j]=='\\') j++;
                                continue;
                            }
                            lcount--;
                            j++;
                            if(s[j]=='\\') j++;          
                        }

                        if (lcount < 0) break;
                        i--;
                        continue;
                    }
                }
                j++;
            }
        } 
        else if (buf[0]=='\0' || buf[0]=='\n') {
            fprintf (out, "%s", buf);
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
