#ifndef TREE_H
#define TREE_H

#include "tree_node.h"
#include <cstring>
class tree
{
    private:
        tree_node *root = nullptr;
        tree_node *current = nullptr;
        enum MENU_ITEMS
        {
            MENU_MENU       = 'm',
            MENU_PRINT      = 'p',
            MENU_CURRENT    = 'c',
            MENU_GO_ROOT    = 'h',
            MENU_GO_LEFT    = 'l',
            MENU_GO_RIGHT   = 'r',
            MENU_ADD_ROOT   = 'a',
            MENU_ADD_LEFT   = 's',
            MENU_ADD_RIGHT  = 't',
            MENU_DEL_ROOT   = 'x',
            MENU_DEL_LEFT   = 'y',
            MENU_DEL_RIGHT  = 'z',
            MENU_KILL       = 'k',
            MENU_WORK       = 'w',
            MENU_EXIT       = 'e'
        };

    public:
        tree ()  = default;
        ~tree () { delete_tree(root); }

        void delete_tree (tree_node * tmp);
        int read (FILE *, int);
        void print (tree_node *tmp, FILE *out = stdout, int space = 1);

//navigation:
        tree_node * get_root  () const { return root; }
        tree_node * get_current  () const { return current; }
        tree_node * get_left () const { if (current) return current -> left;  else return nullptr; }
        tree_node * get_right() const { if (current) return current -> right; else return nullptr; }  

        bool go_root  ();
        bool go_left  ();
        bool go_right ();

//adding:
        bool add_root  (tree_node *elem = nullptr);
        bool add_left  (tree_node *elem = nullptr);
        bool add_right (tree_node *elem = nullptr);
        tree_node * add_elem (tree_node *tmp, tree_node *root);

//deleting:
        void delete_root  ();
        void delete_left_tree  () {   if (current_check ()) return; delete_tree (current -> left ); current -> left = nullptr; }
        void delete_right_tree () {   if (current_check ()) return; delete_tree (current -> right); current -> right= nullptr; }

//other:
        bool is_empty () { return !root; }
        bool current_check () { if (!current) return printf("current isn't set\n"), true; else return false;}
        void print_menu ();
        void menu ();
        
};
#endif






