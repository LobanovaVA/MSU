#ifndef LIST_NODE_H
#define LIST_NODE_H

#include "tree.h"
#include <stdio.h>

class list;
class list_node;
class list_node: public tree
{
	private:
		list_node *next = nullptr;
	public:
		friend class list;

		list_node * get_next () const { return next; }

		void set_next (list_node *elem)	{ this -> next = elem; }
};

#endif
