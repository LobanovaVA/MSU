#ifndef LIST_NODE_H
#define LIST_NODE_H

#include "student.h"

class list;
class list_node;
class list_node: public student
{
	private:
		list_node *next = nullptr;
	public:
		friend class list;

//navigation: 
		list_node * get_next () const { return next; }

//adding:
		bool set_next  (list_node *elem)	
		{ 
			if (this -> next) return false;
			return this -> next = elem, true;
		}
};

#endif
