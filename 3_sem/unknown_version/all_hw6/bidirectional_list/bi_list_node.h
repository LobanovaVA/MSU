#ifndef BI_LIST_NODE_H
#define BI_LIST_NODE_H

#include "student.h"

class bi_list;
class bi_list_node;
class bi_list_node: public student
{
	private:
		bi_list_node *next = nullptr;
		bi_list_node *prev = nullptr;
	public:
		friend class bi_list;

//navigation: 
		bi_list_node * get_next () const { return next; }
		bi_list_node * get_prev () const { return prev; }

//adding:
		bool set_next  (bi_list_node *elem)	
		{ 
			if (this -> next) return false;
			return this -> next = elem, true;
		}

		bool set_prev (bi_list_node *elem)	
		{ 
			if (this -> prev) return false;
			return this -> prev = elem, true;
		}
};

#endif
