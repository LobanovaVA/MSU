#include <stdio.h>
#include <stdlib.h>
#include "strings.h"

size_t strlen_ ( const char *s )
{
	size_t i;
	for ( i = 0; s[i]; i++ );
	return i;
}

char *strcpy_ ( char *string1, const char *string2 )
{
	char *tmp = string1;

	for ( ; *string2; string1++, string2++ )
		*string1 = *string2;

	*string1 = *string2;

	return tmp;
}


char *strcat_ ( char *string1, const char *string2 )
{
	return strcpy_ ( string1 + strlen_ ( string1 ), string2 );
}

int strcmp_ ( char *string1, const char *string2 )
{
	for ( ; *string1 == *string2; string1++, string2++ )
		if ( *string1 == 0 )
			return 0;

	return *string1 - *string2;
}

char *strchr_ ( const char *string, int ch )
{
	for ( ; *string; string++ )
		if ( *string == ch )
			return ( char * ) string;
	return 0;
}

char *strrchr_ ( const char *string, int ch )
{
	char *tmp = 0;
	for ( ; *string; string++ )
		if ( *string == ch )
			tmp = ( char * ) string;
	return tmp;
}

int strcspn_ ( const char *string1, const char *string2 )
{
	unsigned int f[8] = { 0 };
	int i = 0, k;

	for ( i = 0; string2[i]; i++ )
	{
		k = 128 + string2[i];
		f[k >> 5] |= 1 << ( k - ( ( k >> 5 ) << 5 ) );
	}

	for ( i = 0; string1[i]; i++ )
	{
		k = 128 + string1[i];
		if ( ( f[k >> 5] & 1 << ( k - ( ( k >> 5 ) << 5 ) ) ) != 0 )
			return i;
	}
	return i;
}

int strspn_ ( const char *string1, const char *string2 )
{
	int i = 0;
	for ( i = 0; *string1; string1++, i++ )
	{
		if ( strchr_ ( string2, *string1 ) == 0 )
			return i;
	}
	return i;
}

char *strstr_ ( const char *string1, const char *string2 )
{
	int j;
	string1 = strchr_ ( string1, *string2 );
	while ( string1 != 0 )
	{
		for ( j = 1; string2[j]; j++ )
			if ( string1[j] != string2[j] )
				break;
		if ( !string2[j] )
			return ( char * ) string1;
		string1 = strchr_ ( string1 + 1, *string2 );
	}
	return 0;
}

char *strtok_r_ ( char *str, const char *delim, char **saveptr )
{
	int t;
	for ( ; strcspn_ ( str, delim ) == 0; str++ );
	t = strcspn_ ( str, delim );
	str[t] = 0;
	*saveptr = str + t + 1;
	return str;
}