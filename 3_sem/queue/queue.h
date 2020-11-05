#ifndef QUEUE_H
#define QUEUE_H

#include "queue_node.h"

class queue
{
	private:
		queue_node *head = nullptr;
		queue_node *tail = nullptr;
		int size = 0;
	public:
		queue () = default;
		~queue () { delete_queue (); }

		void delete_queue (){ while (head) pop_head(); }
		int read (FILE *);
        void print(FILE *out=stdout);

		void push_tail (queue_node *elem);
		void pop_head ();
		//void edit_tail (queue_node *elem);
		queue_node * get_head () const { return head; }
		
        bool is_empty () { return !head; }
		void menu ();
};
#endif
