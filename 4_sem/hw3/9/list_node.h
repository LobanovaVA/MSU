#ifndef LIST_NODE_H
#define LIST_NODE_H

#include "student.h"
#include <stdio.h>

class list;
class list_node;
class list_node: public student
{
	private:
		list_node *next = nullptr;
		list_node *prev = nullptr;
	public:
		friend class list;
		list_node * get_next () const { return next; }
		void set_next (list_node *next)	{ this -> next = next; }
};

#endif
