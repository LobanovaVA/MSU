#include <stdio.h>
#include <string.h>
#include <iostream>

#include "addition.h"
#include "parser.h"
#include "operation.h"

int operation::init (const char *spaces_str, char *str, char *r)
{
    given_str = str;
    new_str = r;
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


int operation::solve_3(const char *a, const char *b, parser* S, parser* R)
{
    char buf[LEN];
    int count = 0, fl, e, k; FILE *in, *out;
    if (!( in=fopen(a, "r"))) return ERROR_OPEN_A;
    if (!(out=fopen(b, "w"))) return fclose (in), ERROR_OPEN_B;

    while (fgets (buf, LEN, in))
    {
        for (int i = 0; buf [i]; i++) if (buf [i]== '\n') { buf [i] = 0; break; }

        parser line (this -> space_alph, buf);
        for (k = 0; k < line.pos[0]; k++) fprintf (out, "%c", buf[k]);

        e = 0;
        for (int i = 0; line.lens[i] && i < LEN; i++)
        {
            fl = 1;
            for (int j = 0; S -> lens[j] && j < LEN; j++)
            {
                if ( line.lens[i] == S -> lens[j]  && !(strcmp(line.parser_str+line.pos[i], ((S -> parser_str) + (S -> pos[j]))) ) )
                {
                    if (R -> lens[j]) fprintf (out, "%s", (R -> parser_str) + (R -> pos[j]));
                    for (k = line.pos[i] + line.lens[i]; buf[k] && k < line.pos[i+1]; k++) fprintf (out, "%c", buf[k]);
                    fl = 0; e = 1; break;
                }
            }
            if (fl) 
            {
                if (line.lens[i]) fprintf (out, "%s", (line.parser_str) + (line.pos[i]));
                for (k = line.pos[i] + line.lens[i]; buf[k] && k < line.pos[i+1]; k++) fprintf (out, "%c", buf[k]);
                if (!line.pos[i+1]) for (; buf[k]; k++) fprintf (out, "%c", buf[k]);
                    //for (k = line.pos[i]; buf[k] && k < line.pos[i+1]; k++) fprintf (out, "%c", buf[k]);
                    //if (!line.pos[i+1]) for (; buf[k]; k++) fprintf (out, "%c", buf[k]);
            }
        }
        if (e) count++;
        fprintf (out, "\n");
        if (ferror (out)) { fclose (in); fclose (out); return ERROR_WRITE_B;}
        for(k = 0; k<LEN; k++) buf [k] = 0;

    }
    if ( ferror (in)){ fclose (in); fclose (out); return ERROR_READ_A;}
    fclose (in); fclose (out);
    return count;
}
