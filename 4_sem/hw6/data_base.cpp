#include "data_base.h"

int data_base::read (FILE *fp)
{
    char buf[LEN]; int ph, gr;
    while(fscanf (fp, "%s %d %d", buf, &ph, &gr) == 3)
    	insert (buf, ph, gr);

    if (feof(fp)) return ERROR_END_OF_INPUT_FILE;
    return ERROR_READ_A;
}

void data_base::print(FILE* out)
{
    conteiner.print(out);
    search1.print(out);
    for (int i = 0; i< size2; i++)
    {
        fprintf(out, "tree[%5d]:\n", i);
        search2[i].print(search2[i].get_root(), 0, out);
    }
}

int data_base::insert (char *buf, int ph, int gr)
{
	list_node *elem;
    elem = new list_node;
    if (!elem) return ERROR_NOT_ENOUGH_MEMORY;
    int ret = elem -> init(buf, ph, gr);
    if (ret != 0) return delete elem, ERROR_INIT_DATA;

	int p = phone_hash (ph, size2);
	if (search2[p].insert(elem)) return delete elem, ERROR_SAME_DATA;

	
    search1.insert (elem);
    conteiner.insert (elem);
    return 0;
}


list_node * data_base::select (command &line)
{
    list_node *res = nullptr, *res2 = nullptr, *res_or = nullptr;
    search_type s = DEFAULT;
    if (line.oper == OR)
    {
        if (line.c_name  == EQ) s = SEARCH_OR_1;
        if (line.c_phone == EQ) s = SEARCH_OR_2;
    }
    else
    {
        if (line.c_name  == EQ) s = SEARCH1;
        if (line.c_phone == EQ) s = SEARCH2;
    }
    switch (s)
    {
        case SEARCH_OR_2:
        {
            int p = phone_hash (line.get_phone(), size2);
            res = search2[p].search_or (search2[p].get_root(), line, res_or);
            if (line.c_name == EQ)
            {
                int n = name_hash (line.get_name(), size1);
                res2 = search1.search (search1.arr[n], line);
            }
            else res2 = conteiner.search (line);

            if (!res) res = res2;
            else res_or -> next_found = res2;
            break;
        }
        case SEARCH_OR_1:
        {
            int n = name_hash (line.get_name(), size1);
            res = search1.search_or (search1.arr[n], line, res_or);
            res2 = conteiner.search (line);

            if (!res) res = res2;
            else res_or -> next_found = res2;
            break;
        }
        case SEARCH2:
        {
            int p = phone_hash (line.get_phone(), size2);
            res = search2[p].search (search2[p].get_root(), line);
            break;
        }
        case SEARCH1:
        {
            int n = name_hash (line.get_name(), size1);
            res = search1.search (search1.arr[n], line);
            break;
        }
        case DEFAULT: 
        {
            res = conteiner.search (line);
            break;
        }
    }
    return res;
}


int data_base::do_command(command &line) 
{ 
    switch(line.type)
    {
        case CMD_NONE: return 0;
        case QUIT: return 1; 
        case STOP: return 1; 
        case INSERT: insert (line.get_name(), line.get_phone(), line.get_group()); break;
        case SELECT: print_select  (select (line)); break;
        case DELETE: delete_select (select (line)); break;
    }
    return 0;
}

void data_base::print_select (list_node *res) 
{
    list_node * tmp;
    while(res)
    {
        tmp = res -> next_found;
        res -> next_found = nullptr;
        res -> print();
        res = tmp;
    }
}

void data_base::delete_select (list_node *res) 
{
    list_node * tmp;
    while(res)
    {
        tmp = res -> next_found;
        res -> next_found = nullptr;
        int p = phone_hash (res -> get_phone(), size2);
        search2[p].delete_current (res);
        search1.delete_current (res);
        conteiner.delete_current (res);
        res = tmp;
    }
}


int check (list_node *curr, command &line) 
{
    if (line.c_name == COND_NONE && line.c_phone == COND_NONE && line.c_group == COND_NONE) return 1;
    int fl_n = 0;
    switch (line.c_name)
    {
        case COND_NONE: break;
        case EQ: if (strcmp (curr -> get_name(), line.get_name()) == 0) fl_n = 1; break;
        case LT: if (strcmp (curr -> get_name(), line.get_name()) <  0) fl_n = 1; break;
        case GT: if (strcmp (curr -> get_name(), line.get_name()) >  0) fl_n = 1; break;
        case NE: if (strcmp (curr -> get_name(), line.get_name()) != 0) fl_n = 1; break;
        case LE: if (strcmp (curr -> get_name(), line.get_name()) <= 0) fl_n = 1; break;
        case GE: if (strcmp (curr -> get_name(), line.get_name()) >= 0) fl_n = 1; break;
        case LIKE: if (like (curr -> get_name(), line.get_name())) fl_n = 1; break;
    }

    int fl_p = 0;
    switch (line.c_phone)
    {
        case COND_NONE: break;
        case EQ: if (curr -> get_phone() == line.get_phone()) fl_p = 1; break;
        case LT: if (curr -> get_phone() <  line.get_phone()) fl_p = 1; break;
        case GT: if (curr -> get_phone() >  line.get_phone()) fl_p = 1; break;
        case NE: if (curr -> get_phone() != line.get_phone()) fl_p = 1; break;
        case LE: if (curr -> get_phone() <= line.get_phone()) fl_p = 1; break;
        case GE: if (curr -> get_phone() >= line.get_phone()) fl_p = 1; break;
        case LIKE: break;
    }

    int fl_g = 0;
    switch (line.c_group)
    {
        case COND_NONE: break;
        case EQ: if (curr -> get_group() == line.get_group()) fl_g = 1; break;
        case LT: if (curr -> get_group() <  line.get_group()) fl_g = 1; break;
        case GT: if (curr -> get_group() >  line.get_group()) fl_g = 1; break;
        case NE: if (curr -> get_group() != line.get_group()) fl_g = 1; break;
        case LE: if (curr -> get_group() <= line.get_group()) fl_g = 1; break;
        case GE: if (curr -> get_group() >= line.get_group()) fl_g = 1; break;
        case LIKE: break;
    }

    int ans = 0;
    switch (line.oper)
    {
        case OP_NONE:
        {
            if (line.c_name  != COND_NONE) ans = fl_n;
            if (line.c_phone != COND_NONE) ans = fl_p;
            if (line.c_group != COND_NONE) ans = fl_g;
            break;
        }
        case AND:
        {
            if (line.c_name  != COND_NONE && line.c_phone != COND_NONE) ans = fl_n * fl_p;
            if (line.c_name  != COND_NONE && line.c_group != COND_NONE) ans = fl_n * fl_g;
            if (line.c_phone != COND_NONE && line.c_group != COND_NONE) ans = fl_p * fl_g;
            break;
        }
        case OR:
        {
            if (line.c_phone == EQ) fl_p = 0;
            else if (line.c_name == EQ) fl_n = 0;
            if (line.c_name  != COND_NONE && line.c_phone != COND_NONE) ans = fl_n + fl_p;
            if (line.c_name  != COND_NONE && line.c_group != COND_NONE) ans = fl_n + fl_g;
            if (line.c_phone != COND_NONE && line.c_group != COND_NONE) ans = fl_p + fl_g;
            break;
        }
    }

    if (ans != 0) return 1;
    return 0;
    //printf("%d %d %d %d\n", fl_n, fl_p, fl_p, ans);
}



