#include <stdio.h>
#include <string.h>
#include "test.h"

int test(const char *s, const char *buf){
	int i, j=0;
	char n, m;

	for(i=0; buf[i]; i++){
		if(s[i+j]=='['){
			n=s[i+j+1];
			m=s[i+j+3];
			if(buf[i]<n || buf[i]>m) return 0;
			j+=4;
		}

		else{
			if(s[i+j]=='\\') j++;
			if(s[i+j]!=buf[i]) return 0;
		}
	}
	return !s[i+j];
}

