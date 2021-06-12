#include <stdio.h>
#include <string.h>

#define LEN 10001

int
main (void)
{
	char buf[LEN];
	int small = 0, big = 0;
	FILE *in, *out;

	in = fopen ("input.txt", "r");
	out = fopen ("output.txt", "w");

	fgets (buf, LEN, in);
	if (buf[strlen(buf) - 1] == '\n')
		buf[strlen(buf) - 1] = '\0';	

	for (int i = 0; i < (int) strlen (buf); i++)
	{
		if (buf[i] >= 'a' && buf[i] <= 'z')
			small++;
		if (buf[i] >= 'A' && buf[i] <= 'Z')
			big++;
	}		
		
	fprintf (out, "%d %d\n", small, big);

	fclose (in);
	fclose (out);

	return 0;
}