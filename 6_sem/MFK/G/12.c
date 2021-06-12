#include <stdio.h>
#include <string.h>

#define LEN 1001
int
main (void)
{
	char buf[LEN];
	FILE *in, *out;

	in = fopen ("input.txt", "r");
	out = fopen ("output.txt", "w");

	while (fscanf (in, "%s", buf) != EOF) 
		fprintf (out, "%s\n", buf);

	fclose (in);
	fclose (out);

	return 0;
}
