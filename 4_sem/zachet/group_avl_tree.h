#ifndef group_AVL_TREE_H
#define group_AVL_TREE_H

#include "group_avl_tree_node.h"

class group_avl_tree
{
private:
        group_avl_tree_node *root = nullptr;
        int size1 = 0;
        int size2 = 0;

public:
        friend class data_base;
        group_avl_tree ()  = default;
        ~group_avl_tree () {    delete_group_avl_tree (root); size1 = size2 = 0;  }
        void set_size (int n1 = 0, int n2 = 0);

        void print (group_avl_tree_node *tmp, int space = 0, FILE *out = stdout);

        group_avl_tree_node * get_root  () const { return root; }

        group_avl_tree_node * find_min (group_avl_tree_node *ptr);
        group_avl_tree_node * delete_min (group_avl_tree_node *ptr); 
        group_avl_tree_node * delete_current_rec (group_avl_tree_node *ptr, list_node *k);
        void delete_current (list_node *k);
        void delete_group_avl_tree (group_avl_tree_node *tmp);

        group_avl_tree_node * right_rotation(group_avl_tree_node *curr);
        group_avl_tree_node * left_rotation(group_avl_tree_node *curr);
        group_avl_tree_node * balance (group_avl_tree_node *curr);

        int insert (list_node *k); 
        group_avl_tree_node * insert_rec (group_avl_tree_node *ptr, list_node *k, int& ch); 
        void search (group_avl_tree_node *curr, command &line, list_node *&first);
       
};
#endif
