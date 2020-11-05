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

list_node * list::search (command &line)
{
    list_node *curr, *head_found = nullptr;
    for (curr = head; curr; curr = curr -> next)
        if (check (curr, line)) 
            { head_found = curr;break; }

    if (!head_found) return nullptr;
    list_node *curr_found = head_found;
    curr -> next_found = nullptr;

    for (curr = head_found -> next; curr; curr = curr -> next)
        if (check (curr, line)) 
            { 
                curr_found -> next_found = curr;
                curr_found = curr;
                curr -> next_found = nullptr;
            }
    return head_found;
} 
