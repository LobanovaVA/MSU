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
}

int data_base::insert (char *buf, int ph, int gr)
{
	list_node *elem;
    elem = new list_node;
    if (!elem) return ERROR_NOT_ENOUGH_MEMORY;
    int ret = elem -> init(buf, ph, gr);
    if (ret != 0) return delete elem, ERROR_INIT_DATA;

	if (search3.insert(elem)) return delete elem, ERROR_SAME_DATA;
    conteiner.insert (elem);
    return 0;
}

int data_base::do_command(command &line) 
{ 
    switch(line.type)
    {
        case CMD_NONE: return 0;
        case QUIT: return 1; 
        case STOP: return 1; 
        case INSERT: insert (line.get_name(), line.get_phone(), line.get_group()); break;
        case SELECT: 
        {   
            list_node *first = nullptr;
            if (line.c_name != EQ && line.c_phone != EQ && line.c_group == COND_NONE) conteiner.search (line, first);
            else 
            {
                search3.search (search3.get_root(), line, first); 
                if (line.oper == OR && line.c_group == COND_NONE && ( (line.c_phone == EQ && line.c_name != EQ) || (line.c_phone != EQ && line.c_name == EQ) ) )
                    conteiner.search (line, first);
            }
            print_select (first);
            break;
        }
        case DELETE:
        {   
            list_node *first = nullptr;
            if (line.c_name != EQ && line.c_phone != EQ && line.c_group == COND_NONE) conteiner.search (line, first);
            else 
            {
                search3.search (search3.get_root(), line, first); 
                if (line.oper == OR && line.c_group == COND_NONE && ( (line.c_phone == EQ && line.c_name != EQ) || (line.c_phone != EQ && line.c_name == EQ) ) )
                    conteiner.search (line, first);
            }
            delete_select (first);
            break;
        }
    }
    return 0;
}


void data_base::print_select (list_node *res) 
{
    list_node * tmp;
    while (res)
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
    while (res)
    {
        tmp = res -> next_found;
        res -> next_found = nullptr;
        search3.delete_current (res);
        conteiner.delete_current (res);
        res = tmp;
    }
}
