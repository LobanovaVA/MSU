#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "avl_tree_node.h"

class avl_tree
{
private:
        avl_tree_node *root = nullptr;

public:
        friend class data_base;
        friend class group_avl_tree_node;
        avl_tree ()  = default;
        ~avl_tree () {    delete_avl_tree(root);   }

        void print (avl_tree_node *tmp, int space = 0, FILE *out = stdout);

        avl_tree_node * get_root  () const { return root; }

        avl_tree_node * find_min (avl_tree_node *ptr);
        avl_tree_node * delete_min (avl_tree_node *ptr); 
        avl_tree_node * delete_current_rec (avl_tree_node *ptr, list_node *k);
        void delete_current (list_node *k);
        void delete_avl_tree (avl_tree_node *tmp);

        avl_tree_node * right_rotation(avl_tree_node *curr);
        avl_tree_node * left_rotation(avl_tree_node *curr);
        avl_tree_node * balance (avl_tree_node *curr);

        int insert (list_node *k); 
        avl_tree_node * insert_rec (avl_tree_node *ptr, list_node *k, int& ch); 

        void search (avl_tree_node *curr, command &line, list_node *&head_found);
        void search_next_found (avl_tree_node *curr, command &line, list_node *&curr_found);
        void search_or (avl_tree_node *curr, command &line, list_node *&head_found);
        void search_next_found_or (avl_tree_node *curr, command &line, list_node *&curr_found);
       
       
};
#endif
