#ifndef AVL_TREE_NODE_H
#define AVL_TREE_NODE_H

#include "list_node.h"

class avl_tree_node
{
private:
	list_node *orig = nullptr;
	unsigned char height = 1;
	avl_tree_node *left = nullptr;
	avl_tree_node *right = nullptr;

public:
	friend class avl_tree;
    avl_tree_node () = default;
   ~avl_tree_node () = default;
	avl_tree_node (list_node *k) { orig = k; left = right = 0; height = 1; }

	avl_tree_node * get_left  () const { return left;  }
	avl_tree_node * get_right () const { return right; }
	friend unsigned char get_height (avl_tree_node *curr) { if (curr) return curr -> height; else return 0; }
	int get_balance () const { return get_height(right) - get_height(left); }

	void fix_height()
	{
		unsigned char hl = get_height(left), hr = get_height(right);
		this -> height = (hl > hr ? hl : hr) + 1;
	}

};
#endif
