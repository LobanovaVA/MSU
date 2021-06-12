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

	fgets (buf, LEN, in);

	for (int i = 0; i < (int) strlen (buf); i++)
		switch (buf[i])
		{
			case 'a': buf[i] = 'b'; break;
			case 'A': buf[i] = 'B'; break;
			case 'b': buf[i] = 'a'; break;
			case 'B': buf[i] = 'A'; break;
			default: break;
		}

	fprintf (out, "%s", buf);

	fclose (in);
	fclose (out);

	return 0;
}