#ifndef QUEUE_H
#define QUEUE_H

#include "queue_node.h"

class queue
{
	private:
		queue_node *head = nullptr;
		queue_node *tail = nullptr;
		enum MENU_ITEMS
		{
			MENU_MENU 		= 'm',
			//MENU_PRINT 		= 'p',
            MENU_CURRENT    = 'c',
			MENU_ADD 		= 'a',
			MENU_DEL	 	= 'd',
			MENU_KILL 		= 'k',
			MENU_WORK 		= 'w',
			MENU_EXIT 		= 'e'
		};

	public:
		queue () = default;
		~queue () { delete_queue (); }

		void delete_queue (){ while (head) pop_head(); }
		int read (FILE *, int, int, int);
        void print(FILE *out = stdout);

		void push_tail (queue_node *elem = nullptr);
		void pop_head ();
		queue_node * get_head () const { return head; }
		
        bool is_empty () { return !head; }
        void print_menu ();
		void menu ();
};
#endif
