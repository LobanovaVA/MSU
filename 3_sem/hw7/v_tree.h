#ifndef V_TREE_H
#define V_TREE_H

#include "v_tree_node.h"
#include <cstring>
class v_tree
{
    private:

                v_tree_node *root = nullptr;
                v_tree_node *current = nullptr;

                void delete_tree (v_tree_node * tmp);

        public:
                v_tree ()  = default;
                ~v_tree () {    delete_tree(root);   }

                int read (FILE *);
                void print (v_tree_node *tmp, int space = 0, FILE *out = stdout);

//navigation:
                v_tree_node * get_root  () const { return root; }
                v_tree_node * get_current  () const { return current; }
                v_tree_node * get_child  () const;
                v_tree_node * get_brother () const;

                void go_root  () { current = root; }
                bool go_child  ();
                bool go_brother ();

//adding:
                bool add_root  (v_tree_node *elem);
                bool add_child  (v_tree_node *elem);
                bool add_brother (v_tree_node *elem);
                void add_elem (v_tree_node *tmp, v_tree_node *root);

//deleting:
                void delete_root  ();
                void delete_child ();
                void delete_brother ();
                void delete_child_tree ();
                void delete_brother_tree () {   if (current) delete_tree (current -> brother);  }

//solution:
                int solve_1  (v_tree_node *tmp, int k);

                int solve_2  (v_tree_node *tmp, int k);
                int _solve_2 (v_tree_node *tmp, int k, int& ans);

                int solve_3  (v_tree_node *tmp, int k);
    
                int _solve_3 (v_tree_node *tmp, int k, int& ans, int& elem);
                //int _solve_3 (v_tree_node *tmp, int k, int& ans);
                //int _solve_3  (v_tree_node *tmp, int k);

                int solve_4  (v_tree_node *tmp, int k);
                int _solve_4 (v_tree_node *tmp, int k, int n);

                int solve_5 (v_tree_node *tmp, int k);
                
                int solve_6 (v_tree_node *tmp, int k);
                     
//other:
                bool is_empty () { return !root; }
                int amount_of_elements (v_tree_node *tmp);
                int depth (v_tree_node *tmp);
                int width_of_level(v_tree_node *tmp, int need);

        
};
#endif






