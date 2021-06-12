#include <stdio.h>
#include <string.h>

#define LEN 101

void f (FILE *fp, int *b);

void 
f (FILE *fp, int *b)
{
	char word[LEN];
	fscanf (fp, "%s", word);
	for (int i = 0; i < (int) strlen (word); i++)
		b[word[i] - 'a']++;
}
int
main (void)
{
	FILE *in, *out;

	int b1[26] = {0};
	int b2[26] = {0};

	in = fopen ("input.txt", "r");
	out = fopen ("output.txt", "w");

	f (in, b1);
	f (in, b2);

	for (int i = 0; i < 26; i++)
		if (b1[i] == 1 && b2[i] == 1)
			fprintf (out, "%c ", 'a' + i);

	fclose (in);
	fclose (out);
	return 0;
}
