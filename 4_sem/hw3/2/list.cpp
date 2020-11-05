#include "student.h"
#include "list_node.h"
#include "list.h"
#include "addition.h"


list::~list ()
{
    delete_list();
}

void list::delete_list ()
{
        while (head)
        {
            current = head;
            head = head -> next;
            delete current;
        }
        delete head;
}

int list::read (FILE *fp)
{
	int ret;
	delete_list ();
	list_node *next;

	next = new list_node ();
	if (!next) return ERROR_NOT_ENOUGH_MEMORY;
	ret = next -> read (fp);
	if (ret != 0) return delete next, ret;

    next -> prev = nullptr;
	head = current = next; 
	for (;;)
	{
		next = new list_node;
		if (!next) return ERROR_NOT_ENOUGH_MEMORY;
		ret = next -> read (fp);
		if (ret != 0) return delete next, ret;

		current -> next = next;
        next -> prev = current;
		current = next;
		next = nullptr;
	}
	return 0;
}

void list::print (FILE *out)
{
    int i=0; 
    current=head;
    while(current && i<MAX_PRINT)
    {
        current -> print (out);
        current = current -> next;
        i++;
    }
}

void list::solve_1 (student& s)
{
    list_node *tmp;
    current = head;
    if (*current < s) current = current -> next;
    while (current)
    {
        if (*current < s)
        {
            tmp = current;            
            current = current -> prev;
            if (tmp -> next) 
            {
                current -> next = tmp -> next;
                current -> next -> prev = current;
            }
            else current -> next =nullptr;
            
            tmp -> next = head;
            head -> prev = tmp;
            tmp -> prev = nullptr;
            head = tmp;
            
        }
        current = current -> next;
    }
}



void list::solve_2 (int k)
{
    int n=0;
    list_node *d, *c;
    current = head;

    
    while (current)
    {
        n++;
        d = current;
        current = current -> next;
    }
    k%=n;
    d -> next = head;
    head -> prev = d;

    current = head;
    for (int i=0; i<n-k-1; i++) current = current -> next;
    c = current -> next;
    
    current -> next =  nullptr;
    c -> prev = nullptr;
    head = c;


}

