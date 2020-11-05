#include <stdio.h>
#include <string.h>
#include <iostream>

#include "tree.h"
#include "addition.h"
#include <math.h>

int tree::read (FILE *fp, int n3)
{
    int ret;
    delete_tree (root);
    tree_node *elem, *curr;

    elem = new tree_node();
    if (!elem) return ERROR_NOT_ENOUGH_MEMORY;
    ret = elem -> read (fp);
    if (ret !=0) return delete elem, ret;
    root = curr = elem;
    for (int i = 1; i < n3; i++)
    {
        elem = new tree_node();
        if (!elem) return ERROR_NOT_ENOUGH_MEMORY;
        ret = elem -> read (fp);
        if (ret != 0) return delete elem, ret;
        if (!add_elem(elem, root)) return delete elem, ERROR_CANNOT_READ_CLASS;
        elem = nullptr;
    }
    return 0;
}

void tree::print (tree_node *tmp, FILE *out, int space)
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




//navigation:______________________________________________________________________________________________

bool tree::go_root  ()
{
    if (!root) return printf("tree has not root item\n"), false;
    else return current = root, true;
}

bool tree::go_left  () 
{ 
    if (current_check ()) return false;
    if (!(current -> left)) return  printf("current has not left item\n"), false; 
    else return current = current -> left, true; 
}

bool tree::go_right () 
{ 
    if (current_check ()) return false;
    if (!(current -> right)) return  printf("current has not right item\n"), false; 
    else return current = current -> right, true; 
}


//adding:______________________________________________________________________________________________

bool tree::add_root (tree_node *elem)
{
    if (root) return printf("item already exists\n"), false; 
    if (!elem) elem = new tree_node;
    return root = elem, true;
}

bool tree::add_left (tree_node *elem)
{
    if (current_check ()) return false;      
    if (current -> left) return printf("item already exists\n"), false; 
    if (!elem) elem = new tree_node;
    return current -> left = elem, true;
}

bool tree::add_right (tree_node *elem)
{
    if (current_check ()) return false;      
    if (current -> right) return printf("item already exists\n"), false; 
    if (!elem) elem = new tree_node;
    return current -> right = elem, true;
}

tree_node * tree::add_elem(tree_node *tmp, tree_node *root)
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

//deleting:______________________________________________________________________________________________

void tree::delete_tree (tree_node *tmp)
{
    if (tmp)
    {
        delete_tree (tmp -> left );
        delete_tree (tmp -> right);
    }
    if(tmp == root) current = root = nullptr;
    delete tmp;
}

void tree::delete_root ()
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


//others:______________________________________________________________________________________________


 // 🐙 🐢 🐣 🐤 🐥 🐦🐧 🐨 🐩 🐫 🐬 🐭 🐮 🐯 🐰 🐱 🐲 🐳 🐴 🐵 🐶 🐷 🐸 🐹 🐺 🐻 🐼 🌛
void tree::menu ()
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


void tree::print_menu()
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
//solution:______________________________________________________________________________________________

/*
int tree::amount_of_elements (tree_node *tmp)
{
    if (!tmp) return 0;
    return amount_of_elements (tmp -> left) + amount_of_elements (tmp -> right) + 1;
}

int tree::depth (tree_node *tmp)
{
    if (!tmp) return 0;
    int l = depth (tmp -> left );
    int r = depth (tmp -> right);
    return (1 + (l > r ? l : r));
}

int tree::width_of_level(tree_node *tmp, int need)
{
    if(!tmp) return 0;
    if (need == 0) return 1;
    need--;
    return width_of_level (tmp -> left, need) + width_of_level (tmp -> right, need);
}

*/
