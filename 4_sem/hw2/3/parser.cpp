#include <stdio.h>
#include <string.h>
#include <iostream>

#include "addition.h"
#include "parser.h"
#include "operation.h"


int parser::init (int* space_alph, char *readed_str)
{
    for(int k = 0; k<LEN; k++) lens[k] = pos[k] = parser_str [k] = 0;
    strcpy(orig_str, readed_str);
    int i = 0, word_num = 0,  begin;
    strcpy(parser_str, readed_str);
    while (parser_str[i])
    {
        if( space_alph [(unsigned int)parser_str[i]] == 0 && ( i==0 || space_alph [(unsigned int)parser_str[i-1]] == 1 || parser_str[i-1] == 0) )
        {
            pos [word_num] = begin = i;
            while ( parser_str[i] && space_alph [(unsigned int)parser_str [i]] == 0 )  i++;
            parser_str[i] = 0;
            lens [word_num] = i - begin;
            i++; word_num++;
        }
        else 
        {
            parser_str[i]=0;
            i++;
        }
    }
    return 0;
}

void parser::print()
{
    printf ("parser:\n");
    for (int i = 0; i < LEN; i++) { if (lens[i]) printf ("%d %d %s\n", lens [i], pos[i], parser_str + pos[i]); }
    printf("\n\n");
}
