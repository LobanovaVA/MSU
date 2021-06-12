#include <stdio.h>
#include <string.h>

#define LEN 1001

void f (char w[]);

void 
f (char w[])
{
	int i = 0, j, len = (int) strlen (w);
	char tmp;

	while (i < len)
	{
		while (i < len && w[i] == ' ')
			i++;

		tmp = w[i];
		j = i + 1;

		while (j < len && w[j] == ' ')
			j++;

		if (j < len)
		{
			w[i] = w[j];
			w[j] = tmp;
		}

		i = j + 1;
	}
}

int
main (void)
{
	FILE *in, *out;
	char buf[LEN];

	in = fopen ("input.txt", "r");
	out = fopen ("output.txt", "w");

	fgets (buf, LEN, in);
	if (buf[strlen(buf) - 1] == '\n')
		buf[strlen(buf) - 1] = '\0';

	f (buf);
	fprintf (out, "%s", buf);

	fclose (in);
	fclose (out);
	return 0;
}
