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
            if ( (current -> next = tmp -> next) ) 
                current -> next -> prev = current;
            else current -> next = nullptr;
            
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
    if (k<0) k+=n;

    d -> next = head;
    head -> prev = d;

    current = head;
    for (int i=0; i<n-k-1; i++) current = current -> next;
    c = current -> next;
    
    current -> next =  nullptr;
    c -> prev = nullptr;
    head = c;


}

void list::solve_3 ()
{
    list_node *tmp;
    current = head;
    
    while ((tmp = current -> next))
    {   

        if (*current> *tmp)
        {
            if (current == head)
            {   
                tmp -> prev =nullptr;
                delete current;
                head = current = tmp;
            }
            else
            {
            current -> prev -> next = tmp;
            tmp -> prev = current -> prev;
            delete current;
            }
        }
        current = tmp;
    }
}



void list::solve_4 ()
{
    list_node *tmp;
    current = head -> next;
    while ((current -> next))
    {
        if (*current > *(current -> next) && *current > *(current -> prev))
        {
            tmp = current;            
            current = current -> prev;
            if ( (current -> next = tmp -> next) ) 
                current -> next -> prev = current;
            else current -> next = nullptr;
            delete tmp;
        }
        current = current -> next;
    }
}

void list::solve_5 (int k)
{
    int n=1, fl=1;
    list_node *tmp;
    current = head;

    while ((current -> next)) 
    {
        current = current -> next;
        n++;
    }
    if (k>n) k=n;
    while (n > k)
    {
        tmp = current;
        current = tmp -> prev;
        fl = 1;
        n--;
        for (int i=0; i<k; i++)
        {   
            if ( !(*tmp > *current ) )  { fl=0; break; }
            current = current -> prev;
        }
        
        if (fl)
        {
            if ( !(tmp -> next))
            {   
                tmp -> prev -> next = nullptr;
                current = tmp -> prev;
                delete tmp;
                
            }
            else
            {   
                current = tmp -> prev;
                current -> next = tmp -> next;
                tmp -> next -> prev = current;
                delete tmp;
            }
        }
        else current = tmp -> prev;
        
    }
}

void list::solve_6 ()
{
    int m=0, fl=0;
    list_node *tmp, *trash;
    current = head;

    while (current)
    {
        fl = 1; m = 0;
        tmp = current;
        while( (current -> next) && fl)
        {
            if (!(*current > *(current -> next)) ) fl=0;
            else {m++; current = current -> next;}
    
        }
        
        if (m>0)
        {
            if (tmp == head)
            {      
                current = current -> next;             
                if (current) 
                    {
                        current -> prev -> next = nullptr;
                        current -> prev = nullptr;
                    }

                while(tmp) 
                {
                    trash = tmp -> next;
                    delete tmp;
                    tmp = trash;
                }
                
                head = current;
            }
            else
            {

                current = current -> next;       
                if (current) 
                    {
                        tmp -> prev -> next = current;
                        current -> prev -> next = nullptr;
                        current -> prev = tmp -> prev;

                    }
                else tmp -> prev -> next = nullptr;

                
                while(tmp) 
                {
                    trash = tmp -> next;
                    delete tmp;
                    tmp = trash;

                }
                

            }
            
        }
        else current = current -> next;
        
        
    }


}
