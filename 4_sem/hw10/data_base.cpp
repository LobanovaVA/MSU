#include "data_base.h"

int data_base::read (FILE *fp)
{
    char buf[LEN]; int ph, gr;
    while(fscanf (fp, "%s %d %d", buf, &ph, &gr) == 3)
    	insert (buf, ph, gr);

    if (feof (fp)) return ERROR_END_OF_INPUT_FILE;
    return ERROR_READ_A;
}

void data_base::print(FILE* out)
{
    conteiner.print (out);
    search3.print (search3.get_root (), 0, out);
    search4.print(0, out);
    for (int i = 0; i< size2; i++)
    {
        fprintf(out, "tree[%5d]:\n", i);
        search5[i].print(search5[i].get_root(), 0, out);
    }
}

int data_base::insert (char *buf, int ph, int gr)
{
	list_node *elem;
    elem = new list_node;
    if (!elem) return ERROR_NOT_ENOUGH_MEMORY;
    int ret = elem -> init(buf, ph, gr);
    if (ret != 0) return delete elem, ERROR_INIT_DATA;

	if (search3.insert(elem)) return delete elem, ERROR_SAME_DATA;

    search4.insert (elem);
    int p = phone_hash (ph, size2);
    search5[p].insert(elem);
    conteiner.insert (elem);
    return 0;
}

int data_base::do_command(command &line, int fd) 
{ 
    switch(line.type)
    {
        case CMD_NONE: return 0;
        case QUIT: return 1; 
        case STOP: return 2; 
        case INSERT: insert (line.get_name(), line.get_phone(), line.get_group()); break;
        case SELECT: print_select  (select (line), fd); break;
        case DELETE: delete_select (select (line)); break;
    }
    return 0;
}




list_node * data_base::select (command &line)
{
    list_node *first = nullptr;

    if (line.c_group != COND_NONE) return search3.search (search3.get_root(), line, first), first;
    
    if (line.oper == OR && line.c_name == EQ && line.c_phone == EQ)
    {
        int p = phone_hash (line.get_phone(), size2);
        search5[p].search_or (search5[p].get_root(), line, first);
        int n = name_hash (line.get_name(), size1);
        search4.search (search4.arr[n], line, first);
        return first;
    }

    if (line.c_phone == EQ) 
    {
        int p = phone_hash (line.get_phone(), size2);
        search5[p].search (search5[p].get_root(), line, first);
        return first;
    }
    if (line.c_name  == EQ) 
    {
        int n = name_hash (line.get_name(), size1);
        search4.search (search4.arr[n], line, first);
        return  first;
    }
    return conteiner.search (line,  first), first;
}



void data_base::print_select (list_node *res, int fd) 
{
    list_node * tmp;
    while (res)
    {
        tmp = res -> next_found;
        res -> next_found = nullptr;
        res -> Print(fd);
        res = tmp;
    }
}

void data_base::delete_select (list_node *res) 
{
    list_node * tmp;
    while (res)
    {
        tmp = res -> next_found;
        res -> next_found = nullptr;
        search3.delete_current (res);
        search4.delete_current (res);
        int p = phone_hash (res -> get_phone(), size2);
        search5[p].delete_current (res);
        conteiner.delete_current (res);
        res = tmp;
    }
}
