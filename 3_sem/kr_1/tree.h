#ifndef TREE_H
#define TREE_H

#include "tree_node.h"
#include <stdio.h>

class tree
{
    private:
        tree_node *root = nullptr;
        tree_node *current = nullptr;

        void delete_tree (tree_node * tmp);

    public:
        tree ()  = default;
        ~tree () {    delete_tree(root);   }

        int read (FILE *);
        void print (tree_node *tmp, int space = 0, FILE *out = stdout);

//navigation:
        tree_node * get_root  () const { return root; }
        tree_node * get_current  () const { return current; }
        tree_node * get_middle () const;
        tree_node * get_left   () const;
        tree_node * get_right  () const;

        void go_root  () { current = root; }
        bool go_left   ();
        bool go_middle ();
        bool go_right  ();

//adding:
        bool add_root   (tree_node *elem);
        bool add_left   (tree_node *elem);
        bool add_middle (tree_node *elem);
        bool add_right  (tree_node *elem);
        tree_node * add_elem (tree_node *tmp, tree_node *root);

//deleting:
        void delete_root  ();
        void delete_left  ();
        void delete_middle();
        void delete_right ();
        void delete_left_tree   () {   if (current) delete_tree (current -> left  );  }
        void delete_middle_tree () {   if (current) delete_tree (current -> middle);  }
        void delete_right_tree  () {   if (current) delete_tree (current -> right );  }

//solution:
        int solve (tree_node *tmp);
        int c(tree_node *tmp);
};
#endif






