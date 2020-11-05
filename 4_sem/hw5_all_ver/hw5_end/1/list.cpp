//#include "addition.h"
#include "list.h"
//#include "hash.h"
//#include "record.h"
//#include "command.h"

int list::read (FILE *fp, hash& hash_set)
{
    char buf[LEN]; int ph, gr;
    delete_list ();
    while(fscanf (fp, "%s %d %d", buf, &ph, &gr) == 3)
        insert (buf, ph, gr, hash_set);

    if (feof(fp)) return ERROR_END_OF_INPUT_FILE;
    return ERROR_READ_A;
}


int list::insert (char *buf, int ph, int gr, hash& hash_set)
{
    list_node *elem;

    elem = new list_node;
    if (!elem) return ERROR_NOT_ENOUGH_MEMORY;
    int ret = elem -> init(buf, ph, gr);
    if (ret != 0) return delete elem, ret;

    hash_node *elem_h;
    elem_h = new hash_node;
    if (!elem_h) { delete elem; delete elem_h; return ERROR_NOT_ENOUGH_MEMORY; }
    elem_h -> orig = elem;

    int p = name_hash (buf, hash_set.size);
    for (hash_node *tmp = hash_set.arr[p]; tmp; tmp = tmp -> next)
        if (*(elem_h -> orig) == *(tmp -> orig)) { delete elem; delete elem_h; return  ERROR_SAME_DATA; }

    if (!head) head = elem;
    else
    {
        elem -> next = head;
        head -> prev = elem;
        head = elem;
    }

    hash_node *tmp = hash_set.arr[p];
    if (!tmp) hash_set.arr[p] = elem_h;
    else
    {
        elem_h -> next = tmp;
        tmp -> prev = elem_h;
        hash_set.arr[p] = elem_h;
    }

    return 0;
}

void list::print (FILE* out)
{
    int i=0;
    list_node *curr = head;
    while(curr && i<MAX_PRINT)
    {
        curr -> print (out);
        curr = curr -> next;
        i++;
    }
}

void list::delete_head ()
{
    list_node *tmp = head;
    if (head) 
    {
        head = tmp -> next;
        if (tmp -> next) tmp -> next -> prev = nullptr;
        delete tmp;
    }
}

void list::delete_current (list_node *curr)
{
    if (!curr) return;
    if (curr == head) return delete_head();


    if (curr -> next) curr -> next -> prev = curr -> prev;
    curr -> prev -> next = curr -> next;
    delete curr;
}






int list::do_command(command &line, hash& hash_set) 
{ 

    switch(line.type)
    {
        case CMD_NONE: return 0;
        case QUIT: return 1; 
        case STOP: return 1; 
        case INSERT: insert (line.name.get(), line.phone, line.group, hash_set); break;
        case SELECT: 
        {
            //line.print();
            if (line.c_name == EQ)
            {
                int p = name_hash (line.name.get(), hash_set.size);
                hash_node *curr_h = hash_set.arr[p];

                for (;curr_h; curr_h = curr_h -> next)
                    if (search (curr_h -> orig, line))
                        curr_h -> orig -> print();

            }
            else
            {
                list_node *curr;
                for (curr = head; curr; curr = curr -> next)
                    if (search (curr, line)) curr -> print();
            }
            break;

        }

        case DELETE:
        {
            if (line.c_name == EQ)
            {
                int p = name_hash (line.name.get(), hash_set.size);
                hash_node *curr_h = hash_set.arr[p], *tmp_h;

                while (curr_h)
                {
                    if (search (curr_h -> orig, line))
                    {
                        tmp_h = curr_h -> next;
                        list_node *del = curr_h -> orig;
                        if (curr_h == hash_set.arr[p])
                            hash_set.arr[p] = curr_h->next;
                        hash_set.delete_current(curr_h);
                        delete_current (del);
                        curr_h = tmp_h;
                    }
                    else curr_h = curr_h -> next;

                }


            }
            else
            {

                list_node *curr, *tmp;
                for (curr = head; curr;)
                {
                    if (search (curr, line))
                    {
                        tmp = curr -> next;


                        hash_node *del_h = nullptr;
                        int p = name_hash (curr -> get_name(), hash_set.size);
                        hash_node *curr_s = hash_set.arr[p];
                        for (;curr_s; curr_s = curr_s -> next)
                            if (curr_s -> orig == curr)
                            {   del_h = curr_s; break; }

                        if (curr_s == hash_set.arr[p])
                            hash_set.arr[p] = curr_s->next;

                        hash_set.delete_current (del_h);
                        delete_current (curr);
                        curr = tmp;
                    }
                    else curr = curr -> next;
                }
            }
            break;
        }
    }
    return 0;
}


int list::search(list_node *curr, command &line) 
{
    if (line.c_name == COND_NONE && line.c_phone == COND_NONE && line.c_group == COND_NONE) return 1;
    
    int fl_n = 0;
    switch (line.c_name)
    {
        case COND_NONE: break;
        case EQ: if (strcmp (curr -> name.get(), line.name.get()) == 0) fl_n = 1; break;
        case LT: if (strcmp (curr -> name.get(), line.name.get()) <  0) fl_n = 1; break;
        case GT: if (strcmp (curr -> name.get(), line.name.get()) >  0) fl_n = 1; break;
        case NE: if (strcmp (curr -> name.get(), line.name.get()) != 0) fl_n = 1; break;
        case LE: if (strcmp (curr -> name.get(), line.name.get()) <= 0) fl_n = 1; break;
        case GE: if (strcmp (curr -> name.get(), line.name.get()) >= 0) fl_n = 1; break;
        case LIKE: if (like (curr -> name.get(), line.name.get())) fl_n = 1; break;
    }

    int fl_p = 0;
    switch (line.c_phone)
    {
        case COND_NONE: break;
        case EQ: if (curr -> phone == line.phone) fl_p = 1; break;
        case LT: if (curr -> phone <  line.phone) fl_p = 1; break;
        case GT: if (curr -> phone >  line.phone) fl_p = 1; break;
        case NE: if (curr -> phone != line.phone) fl_p = 1; break;
        case LE: if (curr -> phone <= line.phone) fl_p = 1; break;
        case GE: if (curr -> phone >= line.phone) fl_p = 1; break;
        case LIKE: break;
    }

    int fl_g = 0;
    switch (line.c_group)
    {
        case COND_NONE: break;
        case EQ: if (curr -> group == line.group) fl_g = 1; break;
        case LT: if (curr -> group <  line.group) fl_g = 1; break;
        case GT: if (curr -> group >  line.group) fl_g = 1; break;
        case NE: if (curr -> group != line.group) fl_g = 1; break;
        case LE: if (curr -> group <= line.group) fl_g = 1; break;
        case GE: if (curr -> group >= line.group) fl_g = 1; break;
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

    

int list::like (char *str_name, char *str_like) 
{
    int h, g = 0, ret = 1;
    for (h = 0; str_name[h] && str_like[h+g]; h++)
    {
        if (str_like [h+g] == '%') return 1;
        if (str_like [h+g] != '_')
        {
            if (str_like [h+g] == '\\') g++;
            if (str_like [h+g] != str_name [h]) { ret = 0; break;}
        }
        
    }
    if (ret && (str_name[h+g] || str_like[h])) ret = 0;
    if (ret) return 1;
    return 0;

}


/*
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
*/

