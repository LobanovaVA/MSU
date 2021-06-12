#include <stdio.h>
#include <string.h>

#define LEN 1001

int
main (void)
{
	FILE *in, *out;
	char buf[LEN];
	int len;

	in = fopen ("input.txt", "r");
	out = fopen ("output.txt", "w");

	fgets (buf, LEN, in);
	len = strlen (buf);
	if (buf[len - 1] == '\n')
		buf[len - 1] = '\0';
	len = strlen (buf);

	for (int i = 0; i < len; i++)
	{
		if (buf[i] == 'C' && i + 2 < len && buf[i + 1] == 'a' && buf[i + 2] == 'o')
		{
			fprintf (out, "Ling");
			i+=2;
			
		}
		else
			fprintf (out, "%c", buf[i]);
	}

	fclose (in);
	fclose (out);
	return 0;
}
