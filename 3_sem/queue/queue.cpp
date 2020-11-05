#include "queue.h"
#include "queue_node.h"
#include "queue.h"
#include "addition.h"



/*
int queue::read (FILE *fp, int n2, int n3)
{
  queue_node *elem;
  for (int i = 0; i < n2; i++)
    {
      elem = new queue_node;
      new_node->read (fp, n3);
      add (new_node);
    }
  return 0;
}
*/

int queue::read (FILE *fp)
{
	int ret;
	delete_queue ();
	queue_node *elem;

	for (;;)
	{
		elem = new queue_node;
		if (!elem) return ERROR_NOT_ENOUGH_MEMORY;
		ret = elem -> read (fp);
		if (ret != 0) return delete elem, ret;
		push_tail(elem); 
		elem = nullptr;
	}
	return 0;

}

void queue::print (FILE *out)
{
    int i=0; 
    queue_node *curr = head;
    while(curr && i<MAX_PRINT)
    {
        curr -> print (out);
        curr = curr -> get_next();
        i++;
    }
}


void queue::push_tail (queue_node *elem)
{
	if (is_empty ()) head = tail = elem; 
	else tail = tail -> next = elem ;
	size++;
}

void queue::pop_head ()
{
	if (is_empty ()) printf(" Queue is empty!\nCannot delete elem.\n");
	queue_node *new_head = head -> get_next();
	delete head;
	head = new_head;
	size--;
}

