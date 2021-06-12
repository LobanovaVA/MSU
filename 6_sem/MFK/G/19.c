#include <stdio.h>
#include <string.h>

#define LEN 1001

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

	int alf[26] = {0}, j;
	char ans[LEN];
	ans[0] = '\0';

	in = fopen ("input.txt", "r");
	out = fopen ("output.txt", "w");

	f (in, alf);

	for (int i = 0; i < 26; i++)
	{
		for (j = 0; j < alf[i] / 2; j++)
		{
			ans[strlen(ans)] = 'a' + i;
			ans[strlen(ans) + 1] = '\0';
			fprintf (out, "%c", 'a' + i);
		}


		alf[i] -= 2 * j;
	}


	for (int i = 0 /*ans[strlen(ans) - 1] - 'a'*/; i < 26; i++)
		if (alf[i] == 1)
		{
			fprintf (out, "%c", 'a' + i);
			break;
		}

	for (int i = (int) strlen(ans) - 1; i >= 0; i--)
		fprintf (out, "%c", ans[i]);

	fclose (in);
	fclose (out);
	return 0;
}
