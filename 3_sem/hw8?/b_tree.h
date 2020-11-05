#ifndef B_TREE_H
#define B_TREE_H

#include "b_tree_node.h"
#include <cstring>
class v_tree
{
    private:

        int order;
        b_tree_node *root = nullptr;
        b_tree_node *current = nullptr;

    public:
        b_tree (int order);
        ~v_tree () = default;

        int read (FILE *);
        void print (b_tree_node *root, int level = 0, int index = -1);

//navigation:
        int get_order () const { return order; }
        void go_root () { current = root; }
        b_tree_node * get_root  () const { return root; }
        b_tree_node * get_current  () const { return current; }
        
//adding:
        student * insert (student *value, b_tree_node *cur, b_tree_node **p_left, b_tree_node **p_right);
        student * insert_node (student *res, b_tree_node *cur, b_tree_node **p_left, b_tree_node **p_right);
        bool add_root  (v_tree_node *elem);

//deleting:
        void delete_tree (v_tree_node * tmp);
        void delete_root () { if (root && !(root -> child[0])) root -> delete_node(); }

//solution:


                     
//other:
        bool is_empty () { return !root; }



};
#endif






