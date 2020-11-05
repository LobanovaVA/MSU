#ifndef V_TREE_NODE_H
#define V_TREE_NODE_H

#include "student.h"

class v_tree;
class v_tree_node;
class v_tree_node: public student
{
	private:
		v_tree_node *child   = nullptr;
		v_tree_node *brother = nullptr;
	public:
		friend class v_tree;

//navigation: 
		v_tree_node * get_child   () const { return child;   }
		v_tree_node * get_brother () const { return brother; }

//adding:
		bool set_child  (v_tree_node *elem)	
		{ 
			if (this -> child) return false;
			return this -> child  = elem, true;
		}

		bool set_brother (v_tree_node *elem)	
		{ 
			if (this -> brother) return false;
			return this -> brother = elem, true;
		}
};

#endif
