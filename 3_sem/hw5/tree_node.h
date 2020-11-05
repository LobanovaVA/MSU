#ifndef TREE_NODE_H
#define TREE_NODE_H

#include "student.h"

class tree;
class tree_node;
class tree_node: public student
{
	private:
		tree_node *left  = nullptr;
		tree_node *right = nullptr;
	public:
		friend class tree;

//navigation: 
		tree_node * get_left  () const { return left;  }
		tree_node * get_right () const { return right; }

//adding:
		bool set_left  (tree_node *elem)	
		{ 
			if (this -> left ) return false;
			return this -> left  = elem, true;
		}

		bool set_right (tree_node *elem)	
		{ 
			if (this -> right) return false;
			return this -> right = elem, true;
		}
};

#endif
