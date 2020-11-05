#include<stdio.h>
#include<string.h>

char * prob(char *s, const char *t);

char * prob(char *s, const char *t){
    int i;
    for(i=0; s[i]; i++)
        if(s[i]==t[0]) {
            s[i]=0;
            s=strcat(s, s+i+1);
        }
    return s;
}
int main(int argv, char **argc){
	char *s, *t;
	s=argc[1]; t=argc[2];
	s=prob(s, t);
	printf("%s\n", s);
	return 0;
}
