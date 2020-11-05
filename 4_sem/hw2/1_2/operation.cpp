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



int operation::check_one_word (char *readed_str, parser* S)
{
    parser line (this -> space_alph, readed_str);
    //line.print();
    for (int i = 0; line.lens[i] && i < LEN; i++)
    {
        for (int j = 0; S -> lens[j] && j < LEN; j++)
        {
            //printf("%d    %d\n",line.lens[i],S -> lens[j]);
            //printf("%s    %s\n",line.parser_str+line.pos[i], ( (S -> parser_str) + (S -> pos[j])  ) );

            if ( line.lens[i] == S -> lens[j] && !(strcmp (line.parser_str+line.pos[i], ((S -> parser_str) + (S -> pos[j]))) )) return 1;
        }
    }
    return 0;

}



int operation::solve_1(const char *a, const char *b, parser* S)
{
    char buf[LEN];
    int count = 0; FILE *in, *out;
    if (!( in=fopen(a, "r"))) return ERROR_OPEN_A;
    if (!(out=fopen(b, "w"))) return fclose (in), ERROR_OPEN_B;

    while (fgets (buf, LEN, in))
    {
    	for (int i = 0; buf [i]; i++) if (buf [i]== '\n') { buf [i] = 0; break; }
        if (this -> check_one_word (buf, S))
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




int operation::check_all_words (char *readed_str, parser* S)
{
    parser line (this -> space_alph, readed_str);
    int fl;
    for (int i = 0; line.lens[i] && i < LEN; i++)
    {
        fl = 0;
        for (int j = 0; S -> lens[j] && j < LEN; j++)
        {
            if ( line.lens[i] == S -> lens[j]  && !(strcmp(line.parser_str+line.pos[i], ((S -> parser_str) + (S -> pos[j]))) ) )
                { fl = 1; break;}
        }
        if (!fl)
        {
            //for (int k = 0; k<LEN; k++) line.lens[k] = line.pos[k] = 0;
            return 0;
        }
    }
    //for (int k = 0; k<LEN; k++) line.lens[k] = line.pos[k] = 0;
    return 1;
}



int operation::solve_2 (const char *a, const char *b, parser* S)
{

    char buf[LEN];
    int count = 0;FILE *in, *out;
    if (!( in=fopen(a, "r"))) return ERROR_OPEN_A;
    if (!(out=fopen(b, "w"))) return fclose (in), ERROR_OPEN_B;

    while (fgets (buf, LEN, in))
    {
        for (int i = 0; buf [i]; i++) if (buf [i]== '\n') { buf [i] = 0; break; }
        if (this -> check_all_words (buf, S) )
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
    if (ferror (in))
    {
        fclose (in);
        fclose (out);
        return ERROR_READ_A;
    }
    fclose (in);
    fclose (out);
    return count;
}

