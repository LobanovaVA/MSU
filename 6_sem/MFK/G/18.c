#include <stdio.h>
#include <string.h>

#define LEN 1001

int
main (void)
{
	FILE *in, *out;
	char buf[LEN];

	in = fopen ("input.txt", "r");
	out = fopen ("output.txt", "w");

	fscanf (in, "%s", buf);
	fprintf (out, "%s", buf);

	while (fscanf (in, "%s", buf) != EOF) 
		fprintf (out, " %s", buf);


	fclose (in);
	fclose (out);
	return 0;
}
