#include <stdio.h>
#include <string.h>
#include <iostream>

#include "addition.h"
#include "parser.h"
#include "operation.h"

int operation::init (const char *spaces_str, char *str, const char *x)
{
    given_str = str;

    if ( strlen (x)==1 )    { if (!strcmp(x,"=") ) cmp = 1; if (!strcmp(x,"<") ) cmp = 2; if (!strcmp(x,">") ) cmp = 3; }
    else                    { if (!strcmp(x,"<>")) cmp = 4; if (!strcmp(x,"<=")) cmp = 5; if (!strcmp(x,">=")) cmp = 6; }

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








//==============================================================================================================================================================================================================================
//==============================================================================================================================================================================================================================
//4


int operation::solve_4(const char *a, const char *b, parser* S)
{
    char buf[LEN];
    int count = 0; FILE *in, *out;
    if (!( in=fopen(a, "r"))) return ERROR_OPEN_A;
    if (!(out=fopen(b, "w"))) return fclose (in), ERROR_OPEN_B;

    switch (this -> cmp)
    {
        case 1:
        {
            while (fgets (buf, LEN, in))
            {
                for (int i = 0; buf [i]; i++) if (buf [i]== '\n') { buf [i] = 0; break; }
                if (this -> check_one_word_cmp1 (buf, S))
                {
                    fprintf (out, "%s\n", buf);
                    if (ferror (out)) { fclose (in); fclose (out); return ERROR_WRITE_B; }
                    count++;
                }
            }

            break;
        }

        case 2:
        {
            while (fgets (buf, LEN, in))
            {
                for (int i = 0; buf [i]; i++) if (buf [i]== '\n') { buf [i] = 0; break; }
                if (this -> check_one_word_cmp2 (buf, S))
                {
                    fprintf (out, "%s\n", buf);
                    if (ferror (out)) { fclose (in); fclose (out); return ERROR_WRITE_B; }
                    count++;
                }
            }
            break;
        }

        case 3:
        {
            while (fgets (buf, LEN, in))
            {
                for (int i = 0; buf [i]; i++) if (buf [i]== '\n') { buf [i] = 0; break; }
                if (this -> check_one_word_cmp3 (buf, S))
                {
                    fprintf (out, "%s\n", buf);
                    if (ferror (out)) { fclose (in); fclose (out); return ERROR_WRITE_B; }
                    count++;
                }
            }
            break;
        }

        case 4:
        {
            while (fgets (buf, LEN, in))
            {
                for (int i = 0; buf [i]; i++) if (buf [i]== '\n') { buf [i] = 0; break; }
                if (this -> check_one_word_cmp4 (buf, S))
                {
                    fprintf (out, "%s\n", buf);
                    if (ferror (out)) { fclose (in); fclose (out); return ERROR_WRITE_B; }
                    count++;
                }
            }
            break;
        }

        case 5:
        {
            while (fgets (buf, LEN, in))
            {
                for (int i = 0; buf [i]; i++) if (buf [i]== '\n') { buf [i] = 0; break; }
                if (this -> check_one_word_cmp5 (buf, S))
                {
                    fprintf (out, "%s\n", buf);
                    if (ferror (out)) { fclose (in); fclose (out); return ERROR_WRITE_B; }
                    count++;
                }
            }
            break;
        }

        case 6:
        {
            while (fgets (buf, LEN, in))
            {
                for (int i = 0; buf [i]; i++) if (buf [i]== '\n') { buf [i] = 0; break; }
                if (this -> check_one_word_cmp6 (buf, S))
                {
                    fprintf (out, "%s\n", buf);
                    if (ferror (out)) { fclose (in); fclose (out); return ERROR_WRITE_B; }
                    count++;
                }
            }
            break;
        }
    }

    if ( ferror (in)) { fclose (in); fclose (out); return ERROR_READ_A; }
    fclose (in); fclose (out);
    return count;
}




int operation::check_one_word_cmp1 (char *readed_str, parser* S)
{
    parser line (this -> space_alph, readed_str);
    for (int i = 0; line.lens[i] && i < LEN; i++)
        for (int j = 0; S -> lens[j] && j < LEN; j++)
            if ( line.lens[i] == S -> lens[j] && (strcmp ( ((S -> parser_str) + (S -> pos[j])), line.parser_str+line.pos[i]) == 0)) return 1;
    return 0;
}
int operation::check_one_word_cmp2 (char *readed_str, parser* S)
{
    parser line (this -> space_alph, readed_str);
    for (int i = 0; line.lens[i] && i < LEN; i++)
        for (int j = 0; S -> lens[j] && j < LEN; j++)
            if ( strcmp ( ((S -> parser_str) + (S -> pos[j])), line.parser_str+line.pos[i]) < 0) return 1;
    return 0;
}
int operation::check_one_word_cmp3 (char *readed_str, parser* S)
{
    parser line (this -> space_alph, readed_str);
    for (int i = 0; line.lens[i] && i < LEN; i++)
        for (int j = 0; S -> lens[j] && j < LEN; j++)
            if ( strcmp ( ((S -> parser_str) + (S -> pos[j])), line.parser_str+line.pos[i]) > 0) return 1;
    return 0;
}
int operation::check_one_word_cmp4 (char *readed_str, parser* S)
{
    parser line (this -> space_alph, readed_str);
    for (int i = 0; line.lens[i] && i < LEN; i++)
        for (int j = 0; S -> lens[j] && j < LEN; j++)
            if ( strcmp ( ((S -> parser_str) + (S -> pos[j])), line.parser_str+line.pos[i]) != 0) return 1;
    return 0;
}
int operation::check_one_word_cmp5 (char *readed_str, parser* S)
{
    parser line (this -> space_alph, readed_str);
    for (int i = 0; line.lens[i] && i < LEN; i++)
        for (int j = 0; S -> lens[j] && j < LEN; j++)
            if ( strcmp ( ((S -> parser_str) + (S -> pos[j])), line.parser_str+line.pos[i]) <= 0) return 1;
    return 0;
}
int operation::check_one_word_cmp6 (char *readed_str, parser* S)
{
    parser line (this -> space_alph, readed_str);
    for (int i = 0; line.lens[i] && i < LEN; i++)
        for (int j = 0; S -> lens[j] && j < LEN; j++)
            if ( strcmp ( ((S -> parser_str) + (S -> pos[j])), line.parser_str+line.pos[i]) >= 0) return 1;
    return 0;
}


//=================================================================================================================================
//=================================================================================================================================
//5


int operation::solve_5(const char *a, const char *b, parser* S)
{
    char buf[LEN];
    int count = 0; FILE *in, *out;
    if (!( in=fopen(a, "r"))) return ERROR_OPEN_A;
    if (!(out=fopen(b, "w"))) return fclose (in), ERROR_OPEN_B;

    switch (this -> cmp)
    {
        case 1:
        {
            while (fgets (buf, LEN, in))
            {
                for (int i = 0; buf [i]; i++) if (buf [i]== '\n') { buf [i] = 0; break; }
                if (this -> check_all_words_cmp1 (buf, S))
                {
                    fprintf (out, "%s\n", buf);
                    if (ferror (out)) { fclose (in); fclose (out); return ERROR_WRITE_B; }
                    count++;
                }
            }

            break;
        }

        case 2:
        {
            while (fgets (buf, LEN, in))
            {
                for (int i = 0; buf [i]; i++) if (buf [i]== '\n') { buf [i] = 0; break; }
                if (this -> check_all_words_cmp2 (buf, S))
                {
                    fprintf (out, "%s\n", buf);
                    if (ferror (out)) { fclose (in); fclose (out); return ERROR_WRITE_B; }
                    count++;
                }
            }
            break;
        }

        case 3:
        {
            while (fgets (buf, LEN, in))
            {
                for (int i = 0; buf [i]; i++) if (buf [i]== '\n') { buf [i] = 0; break; }
                if (this -> check_all_words_cmp3 (buf, S))
                {
                    fprintf (out, "%s\n", buf);
                    if (ferror (out)) { fclose (in); fclose (out); return ERROR_WRITE_B; }
                    count++;
                }
            }
            break;
        }

        case 4:
        {
            while (fgets (buf, LEN, in))
            {
                for (int i = 0; buf [i]; i++) if (buf [i]== '\n') { buf [i] = 0; break; }
                if (this -> check_all_words_cmp4 (buf, S))
                {
                    fprintf (out, "%s\n", buf);
                    if (ferror (out)) { fclose (in); fclose (out); return ERROR_WRITE_B; }
                    count++;
                }
            }
            break;
        }

        case 5:
        {
            while (fgets (buf, LEN, in))
            {
                for (int i = 0; buf [i]; i++) if (buf [i]== '\n') { buf [i] = 0; break; }
                if (this -> check_all_words_cmp5 (buf, S))
                {
                    fprintf (out, "%s\n", buf);
                    if (ferror (out)) { fclose (in); fclose (out); return ERROR_WRITE_B; }
                    count++;
                }
            }
            break;
        }

        case 6:
        {
            while (fgets (buf, LEN, in))
            {
                for (int i = 0; buf [i]; i++) if (buf [i]== '\n') { buf [i] = 0; break; }
                if (this -> check_all_words_cmp6 (buf, S))
                {
                    fprintf (out, "%s\n", buf);
                    if (ferror (out)) { fclose (in); fclose (out); return ERROR_WRITE_B; }
                    count++;
                }
            }
            break;
        }
    }

    if ( ferror (in)) { fclose (in); fclose (out); return ERROR_READ_A; }
    fclose (in); fclose (out);
    return count;
}



int operation::check_all_words_cmp1 (char *readed_str, parser* S)
{
    parser line (this -> space_alph, readed_str);
    int fl;
    for (int i = 0; line.lens[i] && i < LEN; i++)
    {
        fl = 0;
        for (int j = 0; S -> lens[j] && j < LEN; j++)
        {
            if ( line.lens[i] == S -> lens[j]  && (strcmp(((S -> parser_str) + (S -> pos[j])), line.parser_str+line.pos[i]) == 0 ) )
                { fl = 1; break;}
        }
        if (!fl) return 0;
    }
    return 1;
}
int operation::check_all_words_cmp2 (char *readed_str, parser* S)
{
    parser line (this -> space_alph, readed_str);
    int fl;
    for (int i = 0; line.lens[i] && i < LEN; i++)
    {
        fl = 0;
        for (int j = 0; S -> lens[j] && j < LEN; j++)
        {
            if (strcmp(((S -> parser_str) + (S -> pos[j])), line.parser_str+line.pos[i]) < 0 )
                { fl = 1; break;}
        }
        if (!fl) return 0;
    }
    return 1;
}

int operation::check_all_words_cmp3 (char *readed_str, parser* S)
{
    parser line (this -> space_alph, readed_str);
    int fl;
    for (int i = 0; line.lens[i] && i < LEN; i++)
    {
        fl = 0;
        for (int j = 0; S -> lens[j] && j < LEN; j++)
        {
            if (strcmp(((S -> parser_str) + (S -> pos[j])), line.parser_str+line.pos[i]) > 0 )
                { fl = 1; break;}
        }
        if (!fl) return 0;
    }
    return 1;
}
int operation::check_all_words_cmp4 (char *readed_str, parser* S)
{
    parser line (this -> space_alph, readed_str);
    int fl;
    for (int i = 0; line.lens[i] && i < LEN; i++)
    {
        fl = 0;
        for (int j = 0; S -> lens[j] && j < LEN; j++)
        {
            if (strcmp(((S -> parser_str) + (S -> pos[j])), line.parser_str+line.pos[i]) != 0 )
                { fl = 1; break;}
        }
        if (!fl) return 0;
    }
    return 1;
}
int operation::check_all_words_cmp5 (char *readed_str, parser* S)
{
    parser line (this -> space_alph, readed_str);
    int fl;
    for (int i = 0; line.lens[i] && i < LEN; i++)
    {
        fl = 0;
        for (int j = 0; S -> lens[j] && j < LEN; j++)
        {
            if (strcmp(((S -> parser_str) + (S -> pos[j])), line.parser_str+line.pos[i]) <= 0 )
                { fl = 1; break;}
        }
        if (!fl) return 0;
    }
    return 1;
}
int operation::check_all_words_cmp6 (char *readed_str, parser* S)
{
    parser line (this -> space_alph, readed_str);
    int fl;
    for (int i = 0; line.lens[i] && i < LEN; i++)
    {
        fl = 0;
        for (int j = 0; S -> lens[j] && j < LEN; j++)
        {
            if (strcmp(((S -> parser_str) + (S -> pos[j])), line.parser_str+line.pos[i]) >= 0 )
                { fl = 1; break;}
        }
        if (!fl) return 0;
    }
    return 1;
}
