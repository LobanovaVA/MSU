#ifndef TREE_NODE_H
#define TREE_NODE_H

#include "student.h"

template <class T>
class tree;

template <class T>
class tree_node: public T
{
	private:
		tree_node *left  = nullptr;
		tree_node *right = nullptr;
	public:
		friend class tree <T>;
		tree_node () = default;
		~tree_node () { left = right = nullptr; }

		tree_node * get_left  () const { return left;  }
		tree_node * get_right () const { return right; }
		
		void set_right (tree_node *elem) { this -> right = elem; }
		void set_left  (tree_node *elem) { this -> left  = elem; }	
};

#endif
