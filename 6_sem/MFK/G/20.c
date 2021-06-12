#include <stdio.h>
#include <string.h>

#define LEN 1001

void f (FILE *fp, int *b);

void 
f (FILE *fp, int *b)
{
	char word[LEN];
	fgets (word, LEN, fp);

	if (word[strlen(word) - 1] == '\n')
		word[strlen(word) - 1] = '\0';

	for (int i = 0; i < (int) strlen (word); i++)
		if (word[i] != ' ')
			b[word[i] - 'a']++;
}
int
main (void)
{
	FILE *in;
	int alf[26] = {0}, count = 0;

	in = fopen ("input.txt", "r");

	f (in, alf);

	for (int i = 0; i < 26; i++)
	{
		if (alf[i] % 2 != 0)
			count++;
	}

	if (count <= 1)
		printf ("YES\n");
	else
		printf ("NO\n");

	fclose (in);
	return 0;
}
