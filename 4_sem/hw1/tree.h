#ifndef TREE_H
#define TREE_H

#include "tree_node.h"
#include <cstring>

// 🐙 🐢 🐣 🐤 🐥 🐦🐧 🐨 🐩 🐫 🐬 🐭 🐮 🐯 🐰 🐱 🐲 🐳 🐴 🐵 🐶 🐷 🐸 🐹 🐺 🐻 🐼 🌛

template <class T>
class tree
{
    private:
        tree_node <T> *root = nullptr;
        tree_node <T> *current = nullptr;
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
        ~tree () { delete_tree(root); root = current = nullptr; }

        void delete_tree (tree_node <T> * tmp)
        {
            if (tmp)
            {
                delete_tree (tmp -> left );
                delete_tree (tmp -> right);
            }
            if(tmp == root) current = root = nullptr;
            delete tmp;
        }


        int read (FILE *fp, int n1)
        {
            int ret;
            delete_tree (root);
            tree_node <T> *elem, *curr;

            elem = new tree_node <T>;
            if (!elem) return ERROR_NOT_ENOUGH_MEMORY;
            ret = elem -> read (fp);
            if (ret !=0) return delete elem, ret;
            root = curr = elem;
            for (int i = 1; i < n1; i++)
            {
                elem = new tree_node <T>;
                if (!elem) return ERROR_NOT_ENOUGH_MEMORY;
                ret = elem -> read (fp);
                if (ret != 0) return delete elem, ret;
                if (!add_elem(elem, root)) return delete elem, ERROR_CANNOT_READ_CLASS;
                elem = nullptr;
            }
            return 0;
        }


        void print (tree_node <T> *tmp, FILE *out = stdout, int space = 1)
        {
            //if(space==1) printf("\n 🌿 TREE\n\n");
            if(space==1) printf("🌿\n");
            if(tmp)
            {
                for (int i=0; i<space; i++) fprintf (out, "    ");
                if (tmp == current) printf("👉");
                else printf("  ");
                tmp -> print ();
                if (tmp && space<MAX_PRINT+1)
                {
                    space++;
                    print (tmp -> left , out, space);
                    print (tmp -> right, out, space);
                }
            }
        }

//navigation:
        tree_node <T> * get_root  () const { return root; }
        tree_node <T> * get_current  () const { return current; }
        tree_node <T> * get_left () const { if (current) return current -> left;  else return nullptr; }
        tree_node <T> * get_right() const { if (current) return current -> right; else return nullptr; }  

        bool go_root  ()
        {
            if (!root) return printf("tree has not root item\n"), false;
            else return current = root, true;
        }

        bool go_left  () 
        { 
            if (current_check ()) return false;
            if (!(current -> left)) return  printf("current has not left item\n"), false; 
            else return current = current -> left, true; 
        }

        bool go_right () 
        { 
            if (current_check ()) return false;
            if (!(current -> right)) return  printf("current has not right item\n"), false; 
            else return current = current -> right, true; 
        }

//adding:
        bool add_root (tree_node <T> *elem = nullptr)
        {
            if (root) return printf("item already exists\n"), false; 
            if (!elem) elem = new tree_node <T>;
            return root = elem, true;
        }

        bool add_left (tree_node <T> *elem = nullptr)
        {
            if (current_check ()) return false;      
            if (current -> left) return printf("item already exists\n"), false; 
            if (!elem) elem = new tree_node <T>;
            return current -> left = elem, true;
        }

        bool add_right (tree_node <T> *elem = nullptr)
        {
            if (current_check ()) return false;      
            if (current -> right) return printf("item already exists\n"), false; 
            if (!elem) elem = new tree_node <T>;
            return current -> right = elem, true;
        }

        tree_node <T> * add_elem(tree_node <T> *tmp, tree_node <T> *root)
        {
            if(!root)
            {
                root = tmp;
                return root;
            }
            else
            {
                if (*tmp < *root)
                {
                    tmp = add_elem(tmp, root->left);
                    if (tmp) root -> left = tmp;
                    else return 0;
                }
                else
                {
                    tmp = add_elem(tmp, root-> right);
                    if (tmp) root -> right = tmp;
                    else return 0;
                }
            }
            return root;
        }


//deleting:
        void delete_root  ()
        {
            if (root)
            {
                if (root -> left || root -> right) printf("root has child\n");
                else
                {
                    delete root;
                    current = root = nullptr;
                }
            }
        }
        void delete_left_tree  () {   if (current_check ()) return; delete_tree (current -> left ); current -> left = nullptr; }
        void delete_right_tree () {   if (current_check ()) return; delete_tree (current -> right); current -> right= nullptr; }

//other:
        bool is_empty () { return !root; }
        bool current_check () { if (!current) return printf("current isn't set\n"), true; else return false;}

        void menu ()
        {
            char buf[LEN]; 
            print_menu ();
            for(;;)
            {
                printf("\nEnter command: ");
                if (!(fgets (buf, LEN, stdin))) return;
                enum MENU_ITEMS key = (MENU_ITEMS) buf [0];
                switch (key)
                {
                    case MENU_MENU       : {printf("PRINT TREE MENU:");          print_menu (); break;}
                    case MENU_PRINT      : {printf("PRINT TREE:\n");             print (root); break;}
                    case MENU_CURRENT    : {printf("PRINT TREE CURRENT:\n");     if(!current_check ()) current -> print (); break;}
                    case MENU_GO_ROOT    : {printf("GO TREE ROOT \n");           go_root  (); break;}
                    case MENU_GO_LEFT    : {printf("GO TREE LEFT \n");           go_left  (); break;}
                    case MENU_GO_RIGHT   : {printf("GO TREE RIGHT\n");           go_right (); break;}
                    case MENU_ADD_ROOT   : {printf("ADD ROOT \n");               add_root (); break;}
                    case MENU_ADD_LEFT   : {printf("ADD LEFT \n");               add_left (); break;}
                    case MENU_ADD_RIGHT  : {printf("ADD RIGHT\n");               add_right(); break;}
                    case MENU_DEL_ROOT   : {printf("DELETE ROOT \n");            delete_root (); break;}
                    case MENU_DEL_LEFT   : {printf("DELETE LEFT \n");            delete_left_tree (); break;}
                    case MENU_DEL_RIGHT  : {printf("DELETE RIGHT\n");            delete_right_tree(); break;}
                    case MENU_KILL       : {printf("KILL ALL TREE\n");           delete_tree(root); break;}
                    case MENU_WORK       : {printf("GO INTO NEXT STRUCTURE (STUDENT)\n");     if(!current_check ()) current -> menu (); break; }
                    case MENU_EXIT       : {printf("EXIT INTO PREV STRUCTURE (LIST)\n");      return;}
                }
            }
        }

        void print_menu ()
        {
            printf("\n\n");
            printf("\n               ╔=====🐙 🐯 🐰 🐲 🐢 🐺 🐶 🐷=====╗");
            printf("\n               ║                                 ║");
            printf("\n               ║      TREE MENU:                 ║");
            printf("\n               ║                                 ║");
            printf("\n               ║  m - print menu                 ║");
            printf("\n               ║  p - print tree                 ║");
            printf("\n               ║  c - print tree current         ║");
            printf("\n               ║                                 ║");
            printf("\n               ║  h - go to root                 ║");
            printf("\n               ║  l - go to left                 ║");
            printf("\n               ║  r - go to right                ║");
            printf("\n               ║                                 ║");
            printf("\n               ║  a - add root                   ║");
            printf("\n               ║  s - add left                   ║");
            printf("\n               ║  t - add right                  ║");
            printf("\n               ║                                 ║");
            printf("\n               ║  x - delete root                ║");
            printf("\n               ║  y - delete left  tree          ║");
            printf("\n               ║  z - delete right tree          ║");
            printf("\n               ║  k - kill all tree              ║");
            printf("\n               ║                                 ║");
            printf("\n               ║  w - go into next structure 🐾  ║");
            printf("\n               ║  e - exit                       ║");
            printf("\n               ║                                 ║");
            printf("\n               ╚=================================╝");
            printf("\n\n");         
        }

        
};
#endif






