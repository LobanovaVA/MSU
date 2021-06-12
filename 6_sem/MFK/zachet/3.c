#include <stdio.h>

#define N 1001

int big_count (char *buf, int *ans);

int 
big_count (char *buf, int *ans)
{
	char s = buf[0];

	if (s == 0 || s == '.')
		return *ans;

	if (s >= 'A' && s <= 'Z')
		(*ans)++;

	return big_count (buf + 1, ans);
}

int main (void)
{
	char buf[N];
	int ans = 0;

	scanf ("%[^\n]", buf);

	printf ("%d\n", big_count (buf, &ans));

	return 0;
}