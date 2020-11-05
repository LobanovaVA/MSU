#include <stdio.h>
#include <string.h>
#include <iostream>

#include "addition.h"
#include "parser.h"
#include "operation.h"

int operation::init (const char *spaces_str, char *str)
{
    given_str = str;
    int i = 0;
    while (spaces_str [i])
    {
        if (space_alph [(unsigned int)spaces_str [i]] == 0) space_alph [(unsigned int)spaces_str [i]] = 1;
        i++;
    }
    return 0;
}

void operation::print ()
{
    printf ("S_STR: %s\n", given_str);
    for (int i = 0; i < 256; i++) { if (space_alph[i]) printf ("%d=%d  ", i, space_alph[i]); }
    printf ("\n\n");
}


//=======================================================================================================
//=======================================================================================================
//6

int operation::check_one_word_1symbol (char *readed_str, parser* S)
{
    parser line (this -> space_alph, readed_str);
    for (int i = 0; line.lens[i] && i < LEN; i++)
    {
        for (int j = 0; S -> lens[j] && j < LEN; j++)
        {
            int h, g = 0, ret = 1;
            char *line_word = line.parser_str+line.pos[i];
            char *S_word = (S -> parser_str) + (S -> pos[j]);
            for (h = 0; line_word[h] && S_word[h]; h++)
                if( S_word [h+g] != '_')
                {
                    if (S_word [h+g] == '\\') g++;
                    if (S_word [h+g] != line_word [h]) { ret = 0; break;}
                }
            //if (ret && S_word[h+g]) ret = 0;
            if (ret && (S_word[h+g] || line_word[h])) ret = 0;
            if (ret) return 1;
        }
    }
    return 0;

}



int operation::solve_6(const char *a, const char *b, parser* S)
{
    char buf[LEN];
    int count = 0; FILE *in, *out;
    if (!( in=fopen(a, "r"))) return ERROR_OPEN_A;
    if (!(out=fopen(b, "w"))) return fclose (in), ERROR_OPEN_B;

    while (fgets (buf, LEN, in))
    {
    	for (int i = 0; buf [i]; i++) if (buf [i]== '\n') { buf [i] = 0; break; }
        if (this -> check_one_word_1symbol (buf, S))
    	{
            fprintf (out, "%s\n", buf);
            if (ferror (out))
            {
                fclose (in);
                fclose (out);
                return ERROR_WRITE_B;
            }
            count++;
    	}
    }
    if ( ferror (in))
    {
        fclose (in);
        fclose (out);
        return ERROR_READ_A;
    }

    fclose (in);
    fclose (out);
    return count;
}



//=======================================================================================================
//=======================================================================================================
//7

int operation::check_all_word_1symbol (char *readed_str, parser* S)
{
    parser line (this -> space_alph, readed_str);
    for (int i = 0; line.lens[i] && i < LEN; i++)
    {
        int j = i;
        if (S -> lens[j])
        {
            int h, g = 0; 
            char *line_word = line.parser_str+line.pos[i];
            char *S_word = (S -> parser_str) + (S -> pos[j]);
            for (h = 0; line_word[h]; h++)
                if( S_word [h+g] != '_')
                {
                    if (S_word [h+g] == '\\') g++;
                    if (S_word [h+g] != line_word [h]) return 0;
                }
            if (S_word[h+g] || line_word[h]) return 0;
        }
    }
    return 1;

}



int operation::solve_7(const char *a, const char *b, parser* S)
{
    char buf[LEN];
    int count = 0; FILE *in, *out;
    if (!( in=fopen(a, "r"))) return ERROR_OPEN_A;
    if (!(out=fopen(b, "w"))) return fclose (in), ERROR_OPEN_B;

    while (fgets (buf, LEN, in))
    {
        for (int i = 0; buf [i]; i++) if (buf [i]== '\n') { buf [i] = 0; break; }
        if (this -> check_all_word_1symbol (buf, S))
        {
            fprintf (out, "%s\n", buf);
            if (ferror (out))
            {
                fclose (in);
                fclose (out);
                return ERROR_WRITE_B;
            }
            count++;
        }
    }
    if ( ferror (in))
    {
        fclose (in);
        fclose (out);
        return ERROR_READ_A;
    }

    fclose (in);
    fclose (out);
    return count;
}