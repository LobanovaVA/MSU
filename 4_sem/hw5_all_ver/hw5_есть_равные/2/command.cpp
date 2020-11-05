#include "addition.h"
#include "command.h"

int command::parse ( int *space_alph, const char *str)
{
    char readed_str[LEN];
    strcpy(readed_str, str);

    //name = nullptr;
    phone = -1; group = -1;
    type = CMD_NONE; c_name  = COND_NONE; c_phone = COND_NONE; c_group = COND_NONE; oper = OP_NONE;

    int  pos[15]  = {0};
    int i = 0, word_num = 0,  begin;
    while (readed_str[i])
    {
        if( space_alph[(int)readed_str[i]] == 0 && ( i==0 || space_alph[(int)readed_str[i-1]] == 1 || readed_str[i-1] == 0) )
        {
            pos [word_num] = begin = i;
            while ( readed_str[i] && space_alph [(int)readed_str [i]] == 0 )  i++;
            readed_str[i] = 0;
            i++; word_num++;
        }
        else { readed_str[i]=0; i++; }
    }

    if (!strcmp(readed_str + pos[0], "select"))
    {
        type = SELECT;
        if (!strcmp(readed_str + pos[1], "*"))
            return arg (readed_str, pos, 0);
    }
    else
    {
        if (!strcmp(readed_str + pos[0], "delete"))
        {
            type = DELETE;
            return arg (readed_str, pos, -1);
        }
        else
        {
            if (!strcmp(readed_str + pos[0], "insert"))
            {
                type = INSERT;
                if (!(pos[1] && pos[2] && pos[3])) return ERROR_PARSE_INSERT_ARG;
                name = std::make_unique <char []> (strlen (readed_str + pos[1]) + 1);
                if (!(name)) return ERROR_PARSE_NAME_MEMORY;
                strcpy (name.get(), readed_str + pos[1]);
                phone = atoi (readed_str + pos[2]);
                group = atoi (readed_str + pos[3]);
                return 0;

            }
            else
            {
                if (!strcmp(readed_str + pos[0], "quit")) return type = QUIT, 0;
                else
                {
                    if (!strcmp(readed_str + pos[0], "stop")) return type = STOP, 0;
                    else return ERROR_PARSE_CMD_TYPE;
                }
            }
        }
    }
    return 0;
}

//print & print_cmd=================================================================================================
//================================================================================================================

void command::print (FILE *out)
{
    switch(type)
    {
        case CMD_NONE: break;
        case QUIT: fprintf(out, "quit;\n"); break;
        case STOP: fprintf(out, "stop;\n"); break;
        case INSERT: fprintf(out, "insert (%s, %d, %d);\n", name.get(), phone, group); break;
        case SELECT:
        {
            fprintf(out, "select *");
            // вывод * или перечисление
            print_arg (out);
            break;
        }
        case DELETE: { fprintf(out, "delete"); print_arg (out); break;}
    }
}


void command::print_cmd (FILE *out)
{
    fprintf(out, "║%16s ║%16d ║%6d ║", name.get(), phone, group);

    switch(type)
    {
        case CMD_NONE: fprintf(out, "  NONE  ║  NONE   ║  NONE   ║  NONE   ║ NONE ║\n"); break;
        case QUIT: fprintf(out, "  quit  ║  NONE   ║  NONE   ║  NONE   ║ NONE ║\n"); break;
        case STOP: fprintf(out, "  stop  ║  NONE   ║  NONE   ║  NONE   ║ NONE ║\n"); break;
        case INSERT: fprintf(out, " insert ║  NONE   ║  NONE   ║  NONE   ║ NONE ║\n"); break;
        case SELECT:
        {
            fprintf(out, " select ║");
            print_arg_debug(out);
            break;
        }
        case DELETE: { fprintf(out, " delete ║"); print_arg_debug (out); break;}
    }

}

//================================================================================================================
//arg=============================================================================================================

int command::arg (char *readed_str, int *pos, int i)
{
    if (!pos[i+2]) return 0;
    if (!strcmp(readed_str + pos[i+2], "where"))
    {
        if (!strcmp(readed_str + pos[i+3], "name"))
        {
            if (!strcmp(readed_str + pos[i+4], "="))  c_name = EQ;
            else{
                if (!strcmp(readed_str + pos[i+4], "<"))  c_name = LT;
                else{
                    if (!strcmp(readed_str + pos[i+4], ">"))  c_name = GT;
                    else{
                        if (!strcmp(readed_str + pos[i+4], "<>")) c_name = NE;
                        else{
                            if (!strcmp(readed_str + pos[i+4], "<=")) c_name = LE;
                            else{
                                if (!strcmp(readed_str + pos[i+4], ">=")) c_name = GE;
                                else{
                                    if (!strcmp(readed_str + pos[i+4], "like")) c_name = LIKE;
                                    else return ERROR_PARSE_COND_TYPE;
            }}}}}}
            if (!pos[i+5]) return ERROR_PARSE_DATA_NPG;
            name = std::make_unique <char []> (strlen (readed_str + pos[i+5]) + 1);
            if (!(name)) return ERROR_PARSE_NAME_MEMORY;
            strcpy (name.get(), readed_str + pos[i+5]);
        }
        else
        {
            if (!strcmp(readed_str + pos[i+3], "phone"))
            {
                if (!strcmp(readed_str + pos[i+4], "="))  c_phone = EQ;
                else{
                    if (!strcmp(readed_str + pos[i+4], "<"))  c_phone = LT;
                    else{
                        if (!strcmp(readed_str + pos[i+4], ">"))  c_phone = GT;
                        else{
                            if (!strcmp(readed_str + pos[i+4], "<>")) c_phone = NE;
                            else{
                                if (!strcmp(readed_str + pos[i+4], "<=")) c_phone = LE;
                                else{
                                    if (!strcmp(readed_str + pos[i+4], ">=")) c_phone = GE;
                                    else{
                                        if (!strcmp(readed_str + pos[i+4], "like")) c_phone = LIKE;
                                        else return ERROR_PARSE_COND_TYPE;
                }}}}}}
                if (!pos[i+5]) return ERROR_PARSE_DATA_NPG;
                sscanf(readed_str + pos[i+5], "%d", &phone);
            }
            else
            {
                if (!strcmp(readed_str + pos[i+3], "group"))
                {
                    if (!strcmp(readed_str + pos[i+4], "="))  c_group = EQ;
                    else{
                        if (!strcmp(readed_str + pos[i+4], "<"))  c_group = LT;
                        else{
                            if (!strcmp(readed_str + pos[i+4], ">"))  c_group = GT;
                            else{
                                if (!strcmp(readed_str + pos[i+4], "<>")) c_group = NE;
                                else{
                                    if (!strcmp(readed_str + pos[i+4], "<=")) c_group = LE;
                                    else{
                                        if (!strcmp(readed_str + pos[i+4], ">=")) c_group = GE;
                                        else{
                                            if (!strcmp(readed_str + pos[i+4], "like")) c_group = LIKE;
                                            else return ERROR_PARSE_COND_TYPE;
                    }}}}}}
                    if (!pos[i+5]) return ERROR_PARSE_DATA_NPG;
                    sscanf(readed_str + pos[i+5], "%d", &group);
                }
                else return ERROR_PARSE_C_NPG;
            }
        }


        if (pos[i+6])
        {

            if (!strcmp(readed_str + pos[i+6], "and")) oper = AND;
            else
            {
                if (!strcmp(readed_str + pos[i+6], "or"))  oper = OR;
                else return ERROR_PARSE_OP_TYPE;
            }

            if (!strcmp(readed_str + pos[i+7], "name"))
            {
                if (!strcmp(readed_str + pos[i+8], "="))  c_name = EQ;
                else{
                    if (!strcmp(readed_str + pos[i+8], "<"))  c_name = LT;
                    else{
                        if (!strcmp(readed_str + pos[i+8], ">"))  c_name = GT;
                        else{
                            if (!strcmp(readed_str + pos[8], "<>")) c_name = NE;
                            else{
                                if (!strcmp(readed_str + pos[i+8], "<=")) c_name = LE;
                                else{
                                    if (!strcmp(readed_str + pos[i+8], ">=")) c_name = GE;
                                    else{
                                        if (!strcmp(readed_str + pos[i+8], "like")) c_name = LIKE;
                                        else return ERROR_PARSE_COND_TYPE;
                }}}}}}
                if (!pos[i+5]) return ERROR_PARSE_DATA_NPG;
                name = std::make_unique <char []> (strlen (readed_str + pos[i+9]) + 1);
                if (!(name)) return ERROR_PARSE_NAME_MEMORY;
                strcpy (name.get(), readed_str + pos[i+9]);
            }
            else
            {
                if (!strcmp(readed_str + pos[i+7], "phone"))
                {
                    if (!strcmp(readed_str + pos[i+8], "="))  c_phone = EQ;
                    else{
                        if (!strcmp(readed_str + pos[i+8], "<"))  c_phone = LT;
                        else{
                            if (!strcmp(readed_str + pos[i+8], ">"))  c_phone = GT;
                            else{
                                if (!strcmp(readed_str + pos[i+8], "<>")) c_phone = NE;
                                else{
                                    if (!strcmp(readed_str + pos[i+8], "<=")) c_phone = LE;
                                    else{
                                        if (!strcmp(readed_str + pos[i+8], ">=")) c_phone = GE;
                                        else{
                                            if (!strcmp(readed_str + pos[i+8], "like")) c_phone = LIKE;
                                            else return ERROR_PARSE_COND_TYPE;
                    }}}}}}
                    if (!pos[i+9]) return ERROR_PARSE_DATA_NPG;
                    sscanf(readed_str + pos[i+9], "%d", &phone);
                }
                else
                {
                    if (!strcmp(readed_str + pos[i+7], "group"))
                    {
                        if (!strcmp(readed_str + pos[i+8], "="))  c_group = EQ;
                        else{
                            if (!strcmp(readed_str + pos[i+8], "<"))  c_group = LT;
                            else{
                                if (!strcmp(readed_str + pos[i+8], ">"))  c_group = GT;
                                else{
                                    if (!strcmp(readed_str + pos[i+8], "<>")) c_group = NE;
                                    else{
                                        if (!strcmp(readed_str + pos[i+8], "<=")) c_group = LE;
                                        else{
                                            if (!strcmp(readed_str + pos[i+8], ">=")) c_group = GE;
                                            else{
                                                if (!strcmp(readed_str + pos[i+8], "like")) c_group = LIKE;
                                                else return ERROR_PARSE_COND_TYPE;
                        }}}}}}
                        if (!pos[i+9]) return ERROR_PARSE_DATA_NPG;
                        sscanf(readed_str + pos[i+9], "%d", &group);
                    }
                    else return ERROR_PARSE_C_NPG;
                }
            }
        }
    }
    else return ERROR_PARSE_WHERE;
    return 0;
}

//================================================================================================================
//print_arg=======================================================================================================

void command::print_arg (FILE *out)
{

    if (c_name || c_phone || c_group)
    {
        fprintf(out, " where");
        if (c_name)
        {
            fprintf(out, " name");
            switch (c_name)
            {
                case COND_NONE: break;
                case EQ: fprintf(out, " =");  break;
                case LT: fprintf(out, " <");  break;
                case GT: fprintf(out, " >");  break;
                case NE: fprintf(out, " <>"); break;
                case LE: fprintf(out, " <="); break;
                case GE: fprintf(out, " >="); break;
                case LIKE: fprintf(out, " like"); break;
            }
            fprintf(out, " %s", name.get());
        }
        else
        {
            if (c_phone)
            {
                fprintf(out, " phone");
                switch (c_phone)
                {
                    case COND_NONE: break;
                    case EQ: fprintf(out, " =");  break;
                    case LT: fprintf(out, " <");  break;
                    case GT: fprintf(out, " >");  break;
                    case NE: fprintf(out, " <>"); break;
                    case LE: fprintf(out, " <="); break;
                    case GE: fprintf(out, " >="); break;
                    case LIKE: fprintf(out, " like"); break;
                }
                fprintf(out, " %d", phone);
            }
            else
            {
                if (c_group)
                {
                    fprintf(out, " group");
                    switch (c_group)
                    {
                        case COND_NONE: break;
                        case EQ: fprintf(out, " =");  break;
                        case LT: fprintf(out, " <");  break;
                        case GT: fprintf(out, " >");  break;
                        case NE: fprintf(out, " <>"); break;
                        case LE: fprintf(out, " <="); break;
                        case GE: fprintf(out, " >="); break;
                        case LIKE: fprintf(out, " like"); break;
                    }
                    fprintf(out, " %d", group);
                }
            }
        }

        if (oper)
        {
            switch (oper)
            {
                case OP_NONE: break;
                case AND: fprintf(out, " and");  break;
                case OR:  fprintf(out, " or");   break;
            }

            if (c_phone)
            {
                fprintf(out, " phone");
                switch (c_phone)
                {
                    case COND_NONE: break;
                    case EQ: {fprintf(out, " =");  break;}
                    case LT: {fprintf(out, " <");  break;}
                    case GT: {fprintf(out, " >");  break;}
                    case NE: {fprintf(out, " <>"); break;}
                    case LE: {fprintf(out, " <="); break;}
                    case GE: {fprintf(out, " >="); break;}
                    case LIKE: {fprintf(out, " like"); break;}
                }
                fprintf(out, " %d", phone);
            }
            else
            {
                if (c_group)
                {
                    fprintf(out, " group");
                    switch (c_group)
                    {
                        case COND_NONE: break;
                        case EQ: fprintf(out, " =");  break;
                        case LT: fprintf(out, " <");  break;
                        case GT: fprintf(out, " >");  break;
                        case NE: fprintf(out, " <>"); break;
                        case LE: fprintf(out, " <="); break;
                        case GE: fprintf(out, " >="); break;
                        case LIKE: fprintf(out, " like"); break;
                    }
                    fprintf(out, " %d", group);
                }
            }
        }
    }
    fprintf(out, ";\n");
}

//================================================================================================================
//print_arg_debug=================================================================================================

void command::print_arg_debug (FILE *out)
{
    switch (c_name)
    {
        case COND_NONE: fprintf(out, "  NONE   ║");  break;
        case EQ: fprintf(out, "    =    ║"); break;
        case LT: fprintf(out, "    <    ║"); break;
        case GT: fprintf(out, "    >    ║"); break;
        case NE: fprintf(out, "   <>    ║"); break;
        case LE: fprintf(out, "   <=    ║"); break;
        case GE: fprintf(out, "   >=    ║"); break;
        case LIKE: fprintf(out, "  like   ║"); break;
    }
    switch (c_phone)
    {
        case COND_NONE: fprintf(out, "  NONE   ║");  break;
        case EQ: fprintf(out, "    =    ║"); break;
        case LT: fprintf(out, "    <    ║"); break;
        case GT: fprintf(out, "    >    ║"); break;
        case NE: fprintf(out, "   <>    ║"); break;
        case LE: fprintf(out, "   <=    ║"); break;
        case GE: fprintf(out, "   >=    ║"); break;
        case LIKE: fprintf(out, "  like   ║"); break;
    }
    switch (c_group)
    {
        case COND_NONE: fprintf(out, "  NONE   ║");  break;
        case EQ: fprintf(out, "    =    ║"); break;
        case LT: fprintf(out, "    <    ║"); break;
        case GT: fprintf(out, "    >    ║"); break;
        case NE: fprintf(out, "   <>    ║"); break;
        case LE: fprintf(out, "   <=    ║"); break;
        case GE: fprintf(out, "   >=    ║"); break;
        case LIKE: fprintf(out, "  like   ║"); break;
    }
    switch (oper)
    {
        case OP_NONE: fprintf(out, " NONE ║\n");  break;
        case AND: fprintf(out, "  and ║\n"); break;
        case OR:  fprintf(out, "  or  ║\n"); break;
    }
}
