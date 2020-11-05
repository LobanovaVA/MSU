#ifndef LIST_NODE_H
#define LIST_NODE_H

#include "tree.h"
#include <stdio.h>

template <class T, template <class> class T1>
class list;

template <class T, template <class> class T1>
class list_node: public T1 <T>
{
	private:
		list_node *next = nullptr;
	public:
		friend class list <T, T1>;
		list_node () = default;
		~list_node () { next = nullptr; }

		list_node * get_next () const { return next; }

		void set_next (list_node *elem)	{ this -> next = elem; }
};

#endif
