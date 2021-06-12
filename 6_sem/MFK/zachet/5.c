#include <stdio.h>
#include <string.h>

#define LEN 1001

void print_rare_symbol (char str[]);

void 
print_rare_symbol (char str[])
{
	char alf[26] = {0};
	int min;

	for (int i = 0; str[i]; i++)
		if (str[i] >= 'a' && str[i] <= 'z')
			alf[str[i] - 'a']++;
	

	for (int i = 0; i < 26; i++)
		if (alf[i] != 0)
		{
			min = alf[i];
			break;
		}

	for (int i = 0; i < 26; i++)
		if (alf[i] != 0 && alf[i] < min)
			min = alf[i];

	for (int i = 0; i < 26; i++)
		if (alf[i] == min)
		{
			printf("%c %d\n", i + 'a', min);
			break;
		}
}

int main (void)
{
	char str[LEN];
	scanf("%[^\n]", str);

	print_rare_symbol (str);
	return 0;
}