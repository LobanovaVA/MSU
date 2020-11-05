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
        //head = current = nullptr;
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
	/*
    if (ret < 0)
    {
        delete next;
        delete_list();
        return ret;
    }
	//if (ret > 0) return delete next, ret;
    */
	head = current = next; 
	for (;;)
	{
		next = new list_node;
		if (!next) return ERROR_NOT_ENOUGH_MEMORY;
		ret = next -> read (fp);
		if (ret != 0) return delete next, ret;
		/*
        if (ret < 0)
        {
            delete next;
            delete_list();
            return ret;
        }
		//if (ret > 0) return delete next, ret;
		*/
		current -> next = next;
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
