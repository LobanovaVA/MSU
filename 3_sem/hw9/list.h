#ifndef LIST_H
#define LIST_H

#include "list_node.h"

class list
{
	private:
		list_node *head = nullptr;
		list_node *current = nullptr;
        enum MENU_ITEMS
        {
            MENU_MENU       = 'm',
            MENU_PRINT      = 'p',
            MENU_CURRENT    = 'c',
            MENU_GO_HEAD    = 'h',
            MENU_GO_NEXT    = 'n',
            MENU_ADD_HEAD   = 'a',
            MENU_ADD_NEXT   = 's',
            MENU_DEL_HEAD   = 'x',
            MENU_DEL_NEXT   = 'y',
            MENU_KILL       = 'k',
            MENU_WORK       = 'w',
            MENU_EXIT       = 'e'
        };

	public:
		list () = default;
		~list () { delete_list(); }

		void delete_list () { while (head) delete_head(); }
        int read (FILE *, int, int);
        void print(FILE *out = stdout);      

//navigation:
        list_node * get_current () const { return current; }
        list_node * get_head () const { return head; }
        list_node * get_next () const { if (current) return current -> next; else return nullptr; } 

        void go_head () { current = head; }
        bool go_next () 
        { 
            if (current_check ()) return false;
            if (!(current -> next)) return  printf("current has not next item\n"), false; 
            else return current = current -> next, true; 
        }

//adding:
        bool add_head (list_node *elem = nullptr);
        bool add_next (list_node *elem = nullptr);
      
//deleting:
        void delete_head ();
        void delete_next ();

//other:
        bool current_check () { if (!current) return printf("current isn't set\n"), true; else return false;}
        bool is_empty () { return !head; }
        void print_menu ();
        void menu ();
};
#endif