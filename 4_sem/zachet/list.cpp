#include "list.h"

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
    if (curr == head) return delete_head ();
    if (curr -> next) curr -> next -> prev = curr -> prev;
    curr -> prev -> next = curr -> next;
    delete curr;
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

int list::insert (list_node *elem)
{
    if (!head) head = elem;
    else
    {
        elem -> next = head;
        head -> prev = elem;
        head = elem;
    }

    return 0;
}


void list::search (command &line, list_node *&head_found)
{
    list_node *curr;
    for (curr = head; curr; curr = curr -> next)
        if (check (curr, line)) 
        { 
            curr -> next_found = head_found;
            head_found = curr;
        }
    return;
} 



//SORT//////////////////////////////////////////////////////////////////



void list::linear_insertion_sort (command &line)
{
    bool fl;
    list_node *i = head_found, *j;
    while (i -> next_found)
    {
        fl = true;
        j = head_found;
        if (cmp (i -> next_found, j, line))
        {
            fl = false;
            list_node *tmp = cut_next(i);
            add_before_head (tmp);
        }
        else
        {
            for (j = head_found; j != i ; j = j -> next_found)
            {
                if (cmp (i -> next_found, j -> next_found, line))
                {
                    fl = false;
                    insert_sort (j, i);
                    break;
                }
            }
        }
        if(fl) i = i -> next_found;
    }
}

void list::insert_sort (list_node *j, list_node *i)
{
    list_node *b = j -> next_found, *e = i -> next_found, *f = e -> next_found;
    i -> next_found = f;
    j -> next_found = e;
    e -> next_found = b;
}


list_node * list::cut_next (list_node *current)
{
    if (current) 
    {
        list_node *tmp = current -> next_found;
        if (tmp)
        {
            current -> next_found = tmp -> next_found;
            return tmp;
        }
    }
    return nullptr;
}


bool list::add_before_head (list_node *elem)
{ 

    if (!elem) return false; 
    if (head_found == nullptr) return add_head(elem);

    list_node *tmp = head_found;

    head_found = elem;
    head_found -> next_found = tmp;
    return true; 
}

bool list::add_head (list_node *elem) 
{ 
    if (head_found || !elem) return false; 
    head_found = elem;
    head_found -> next_found = nullptr;
    return true; 
}

bool list::cmp (list_node *x, list_node *y, command &line)
{
    switch(line.par)
    {
        case PAR_NONE: break;
        case NAME:  return strcmp(x -> get_name(), y -> get_name()); 
        case PHONE: return x -> get_phone() < y -> get_phone(); 
        case GROUP: return x -> get_group() > y -> get_group();
    }
    return 0;
}






void list::Neuman_sort (command &line){
    list_node *cur_head, *last;
    if (!head_found) return;
    size_t k = 1;
    while (true) {
        head_found = merge (head_found, k, last, line);
        if (!(last -> next_found)) return;
        while (last -> next_found) 
        {
            cur_head = last;
            cur_head -> next_found = (merge (last -> next_found, k, last, line) );
        }
        k *= 2;
    }
    return;
}

list_node * list::merge (list_node *cur_head, size_t k, list_node * & last, command &line) {
    list_node *ret, *beg1, *end1, *beg2, *end2, *tail;
    size_t i;
    beg1 = end1 = cur_head;

    for (i = 1; i < k; i ++) 
    {
        if (!(end1 -> next_found)) return last = end1, cur_head;
        end1 = end1 -> next_found;
    }

    beg2 = end2 = end1 -> next_found;
    end1 -> next_found = nullptr;
    if (!beg2) return last = end1, cur_head;

    for (i = 1; i < k && end2 -> next_found; i++) 
        end2 = end2 -> next_found;
    
    tail = end2 -> next_found;
    end2 -> next_found = nullptr;

    if (cmp(beg1, beg2, line)) { ret = last = beg1; beg1 = beg1 -> next_found; } 
    else                 { ret = last = beg2; beg2 = beg2 -> next_found; }

    while (beg1 && beg2) 
    {
        if (cmp(beg1, beg2, line)) { last -> next_found = beg1; last = beg1; beg1 = beg1 -> next_found; } 
        else                 { last -> next_found = beg2; last = beg2; beg2 = beg2 -> next_found; }
    }

    if (beg1) { last -> next_found = beg1; last = end1; } 
    else      { last -> next_found = beg2; last = end2; }
    last -> next_found = tail;
    return ret;
}



