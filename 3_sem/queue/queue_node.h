#ifndef QUEUE_NODE_H
#define QUEUE_NODE_H

#include "student.h"
#include <stdio.h>

class queue;
class queue_node;
class queue_node: public student
{
	private:
		queue_node *next = nullptr;
	public:
		friend class queue;
		queue_node * get_next () const { return next; }
		void set_next (queue_node *elem) { this -> next = elem; }


};

#endif
