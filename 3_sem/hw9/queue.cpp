#include <stdio.h>
#include <string.h>
#include <iostream>

#include "queue.h"
#include "queue_node.h"
#include "queue.h"
#include "addition.h"

int queue::read (FILE *fp, int n1, int n2, int n3)
{
	int ret;
	delete_queue ();
	queue_node *elem;
	for (int i = 0; i < n1; i++)
	{
		elem = new queue_node;
		if (!elem) return ERROR_NOT_ENOUGH_MEMORY;
		ret = elem -> read (fp, n2, n3);
                if (ret < 0) return delete elem, ret;
		if (ret > 0) return delete elem, ERROR_NOT_ENOUGH_DATA;
		push_tail(elem); 
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
        curr = curr -> next;
        i++;
    }
}

void queue::push_tail (queue_node *elem)
{
	if (!elem) elem = new queue_node;
	if (is_empty ()) head = tail = elem; 
	else 
	{
                tail -> next = elem;
		tail = elem ;
	}
}

void queue::pop_head ()
{
	if (!is_empty ())
	{
                queue_node *new_head = head -> next;
		delete head;
		head = new_head;
	}
}

 // 🐙 🐢 🐣 🐤 🐥 🐦🐧 🐨 🐩 🐫 🐬  🐯 🐰 🐲 🐳 🐴 🐶 🐷 🐸 🐹 🐺 🐻 🐼 🌛
void queue::menu ()
{
	char buf[LEN]; 
	print_menu ();
	for(;;)
	{
                printf("\nEnter command: ");
		if (!(fgets (buf, LEN, stdin))) return;
		enum MENU_ITEMS key = (MENU_ITEMS) buf [0];

		switch (key)
		{
                        case MENU_MENU		: {printf("PRINT QUEUE MENU:");			print_menu (); break;}
                        //case MENU_PRINT		: {printf("PRINT QUEUE:\n");			print (); break;}
                        case MENU_CURRENT	: {printf("PRINT QUEUE HEAD:\n");		if (head) head -> print (); break;}
                        case MENU_ADD		: {printf("ADD ELEM (PUSH_TAIL)\n");		push_tail (); break;}
                        case MENU_DEL 		: {printf("DELETE ELEM (POP HEAD)\n");          pop_head (); break;}
                        case MENU_KILL		: {printf("KILL ALL QUEUE\n");			delete_queue (); break;}
                        case MENU_WORK		: {printf("GO INTO NEXT STRUCTURE (LIST)\n");	if (head) head -> menu (); break;}
			case MENU_EXIT		: return;
		}
        }
}


void queue::print_menu()
{
	printf("\n\n");
        printf("\n               ╔=====🐙 🐯 🐰 🐲 🐢 🐺 🐶 🐷=====╗");
        printf("\n               ║                                 ║");
        printf("\n               ║      QUEUE MENU:                ║");
        printf("\n               ║                                 ║");
        printf("\n               ║  m - print menu                 ║");
        //printf("\n               ║  p - print queue                ║");
        printf("\n               ║  c - print queue head           ║");
        printf("\n               ║                                 ║");
        printf("\n               ║  a - add to tail                ║");
        printf("\n               ║                                 ║");
        printf("\n               ║  d - pop head                   ║");
        printf("\n               ║  k - kill all queue 🔫          ║");
        printf("\n               ║                                 ║");
        printf("\n               ║  w - go into next structure 🐾  ║");
        printf("\n               ║  e - exit                       ║");
        printf("\n               ║                                 ║");
        printf("\n               ╚=================================╝");
	printf("\n\n");			
}










