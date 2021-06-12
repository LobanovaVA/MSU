#include <stdio.h>
#include <string.h>

#define LEN 1001

int
main (void)
{
	FILE *in, *out;
	char buf[LEN];
	int alf[256] = {0};

	in = fopen ("input.txt", "r");
	out = fopen ("output.txt", "w");

	fgets (buf, LEN, in);
	if (buf[strlen(buf) - 1] == '\n')
		buf[strlen(buf) - 1] = '\0';

	for (int i = 0; i < (int) strlen (buf); i++)
		alf[(int) buf[i]]++;

	for (int i = 0; i < (int) strlen(buf); i++)
		if (buf[i] != ' ' && alf[(int) buf[i]] > 0)
		{
			fprintf (out, "%c", buf[i]);
			alf[(int) buf[i]] = 0;
		}

	fclose (in);
	fclose (out);
	return 0;
}
