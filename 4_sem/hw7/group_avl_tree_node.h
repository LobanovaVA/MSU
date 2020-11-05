#ifndef GROUP_AVL_TREE_NODE_H
#define GROUP_AVL_TREE_NODE_H

#include "list.h"
#include "hash.h"
#include "avl_tree.h"

class group_avl_tree_node
{
private:
    int group = -1;
    int size1 = 0;
    int size2 = 0;
    
    hash search1;
    avl_tree *search2 = nullptr;


    unsigned char height = 1;
    group_avl_tree_node *left = nullptr;
    group_avl_tree_node *right = nullptr;
public:
    friend class group_avl_tree;
    friend int check (list_node *curr, command &line);
    group_avl_tree_node () = default;
   ~group_avl_tree_node () { delete[] search2; size1 = size2 = 0; group = -1; }
    group_avl_tree_node (int n1, int n2, list_node *k = nullptr);

    group_avl_tree_node * get_left  () const { return left;  }
    group_avl_tree_node * get_right () const { return right; }
    friend unsigned char get_height (group_avl_tree_node *curr) { if (curr) return curr -> height; else return 0; }
    int get_balance () const { return get_height(right) - get_height(left); }

    void fix_height()
    {
        unsigned char hl = get_height(left), hr = get_height(right);
        this -> height = (hl > hr ? hl : hr) + 1;
    }

    void delete_current (list_node *k);
    int get_group () { return group; }

    void print (int space = 0, FILE* out = stdout);

    int insert (list_node *elem);
    void select (command &line, list_node *&first);
    void def_search (command &line, list_node *&first);

};

#endif
