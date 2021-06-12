#include <stdio.h>
#include <string.h>

#define LEN 101
int
main (void)
{
	int len;
	char buf[LEN], chek;
	FILE *in, *out;

	in = fopen ("input.txt", "r");
	out = fopen ("output.txt", "w");

	fgets (buf, LEN, in);
	len = strlen(buf);

	if (buf[len - 1] == '\n')
	{
		buf[len - 1] = '\0';			
		len = strlen(buf);
	}

	chek = buf[len - 1];

	for (int i = 0; i < len - 1; i++)
		if (buf[i] == chek)
			fprintf (out, "%d ", i);

	fclose (in);
	fclose (out);

	return 0;
}