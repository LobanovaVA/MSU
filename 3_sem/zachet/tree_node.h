#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>

class tree;
class tree_node;
class tree_node
{
    private:
        char *name;
        tree_node *left   = nullptr;
        tree_node *right  = nullptr;
    public:
        friend class tree;
        
        tree_node (const char *iname = nullptr);
        tree_node (const tree_node& rhs);
        
        ~tree_node();
        void destroy ();
        int init (const char *iname);
        
        tree_node& operator= (const tree_node& x);
        int operator< (const tree_node& x);
        int operator> (const tree_node& x); 
        
        int read (FILE* fp);
        void print (FILE* out = stdout);
        
//navigation: 
        tree_node * get_left   () const { return left;   }
        tree_node * get_right  () const { return right;  }

//adding:
        bool set_left   (tree_node *elem);
        bool set_right  (tree_node *elem);
};
#endif
