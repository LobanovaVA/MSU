#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


int main(void)
{
	FILE *out;
	const char * ar[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "k", "m", "n", "p", "o", "u", "w", "v", "l", "y",
        "x", "z"};
	int x,i;
	if(!(out = fopen("output.txt","w")))
	{ fclose(out);
		return -1;}
	
	for(i = 0; i<1000000; i++)
	{
		x=random()%6;
		fprintf(out,"%s%s%s%s%s%s%s%s%s%s %d\n",ar[random()%21],ar[random()%21],ar[random()%21],ar[random()%21],ar[random()%21],ar[random()%21],ar[random()%21],ar[random()%21],ar[random()%21],ar[random()%21],x);
	}
	fclose (out);
	return 0;
}
