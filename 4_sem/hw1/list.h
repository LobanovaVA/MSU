#ifndef LIST_H
#define LIST_H

#include "list_node.h"

 // 🐙 🐢 🐣 🐤 🐥 🐦🐧 🐨 🐩 🐫 🐬 🐭 🐮 🐯 🐰 🐱 🐲 🐳 🐴 🐵 🐶 🐷 🐸 🐹 🐺 🐻 🐼 🌛

template <class T, template <class> class T1>
class list
{
	private:
		list_node <T, T1> *head = nullptr;
		list_node <T, T1> *current = nullptr;
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
		~list () { delete_list(); head = current = nullptr; }

		void delete_list () { while (head) delete_head(); }

        int read (FILE *fp, int n2, int n1)
        {
            int ret;
            delete_list ();
            list_node <T, T1> *elem, *curr;

            elem = new list_node <T, T1>;
            if (!elem) return ERROR_NOT_ENOUGH_MEMORY;
            ret = elem -> read (fp, n1);
            if (ret != 0) return delete elem, ret;
                head = curr = elem;

            for (int i = 1; i < n2; i++)
            {
                    elem = new list_node <T, T1>;
                    if (!elem) return ERROR_NOT_ENOUGH_MEMORY;
                    ret = elem -> read (fp, n1);
                    if (ret != 0) return delete elem, ret;
                    curr -> next = elem;
                    curr = elem;
                    //elem = nullptr;
            }
            return 0;
        }

        void print(FILE *out = stdout)
        {
            printf("\n╔=============================================================╗");
            printf("\n║                          👀 LIST                            ║\n");
            int i = 0;
            list_node <T, T1> *curr = head;
            while (curr && i<MAX_PRINT)
            {
                if(curr==current) printf("  👉");
                else printf("    ");
                curr -> print ( curr -> get_root(), out);
                curr = curr -> next;
                i++;
            }
            printf("\n╚=============================================================╝");
        }     

//navigation:
        list_node <T, T1> * get_current () const { return current; }
        list_node <T, T1> * get_head () const { return head; }
        list_node <T, T1> * get_next () const { if (current) return current -> next; else return nullptr; } 

        void go_head () { current = head; }
        bool go_next () 
        { 
            if (current_check ()) return false;
            if (!(current -> next)) return  printf("current has not next item\n"), false; 
            else return current = current -> next, true; 
        }

//adding:
        bool add_head (list_node <T, T1> *elem = nullptr) 
        { 
            if (!elem) elem = new list_node <T, T1>;
            if (!head)
            {
                head = elem;
                head -> next = nullptr;
            }
            else
            {
                elem -> next = head;
                head = elem;
            }
            return true; 
        }
        bool add_next (list_node <T, T1> *elem = nullptr)
        { 
            //if (head == nullptr) return add_head(elem);   //если нет головы добавитьв голову 
            if (current_check ()) return false;             
            //if (current -> next) return printf("item already exists\n"), false; //если next уже есть RETURN
            if (!elem) elem = new list_node <T, T1>;
            list_node <T, T1> *ptr = current -> next;
            current -> next = elem;
            elem -> next = ptr;
            return true; 
        }
      
//deleting:
         //удаляет голову и ставит новую голову
        void delete_head ()
        {
            list_node <T, T1> *tmp = head;
            if (head) 
            {
                head = tmp -> next;
                if (current == tmp) current = nullptr;
                delete tmp;
            }
        }

        void delete_next ()
        {
            if(current_check ()) return;
            list_node <T, T1> *tmp = current -> next;
            if (tmp)
            {
                current -> next = tmp -> next;
                delete tmp;
            }
        }

//other:
        bool current_check () { if (!current) return printf("current isn't set\n"), true; else return false;}
        bool is_empty () { return !head; }

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
                    case MENU_MENU       : {printf("PRINT LIST MENU:");          print_menu (); break;}
                    case MENU_PRINT      : {printf("PRINT LIST:\n");             print (); break;}
                    case MENU_CURRENT    : {printf("PRINT LIST CURRENT:\n");     if(!current_check ()) current -> print (current -> get_root()); break;}
                    case MENU_GO_HEAD    : {printf("GO LIST HEAD\n");            go_head (); break;}
                    case MENU_GO_NEXT    : {printf("GO LIST NEXT\n");            go_next (); break;}
                    case MENU_ADD_HEAD   : {printf("ADD HEAD\n");                add_head(); break;}
                    case MENU_ADD_NEXT   : {printf("ADD NEXT\n");                add_next(); break;}
                    case MENU_DEL_HEAD   : {printf("DELETE HEAD\n");             delete_head(); break;}
                    case MENU_DEL_NEXT   : {printf("DELETE NEXT\n");             delete_next(); break;}
                    case MENU_KILL       : {printf("KILL ALL LIST\n");           delete_list(); break;}
                    case MENU_WORK       : {printf("GO INTO NEXT STRUCTURE (LIST)\n");    if(!current_check ()) current -> menu (); break;}
                    case MENU_EXIT       : {printf("EXIT INTO PREV STRUCTURE (QUEUE)\n");  return;}
                }
            }
        }

        void print_menu()
        {
            printf("\n\n");
            printf("\n               ╔=====🐙 🐯 🐰 🐲 🐢 🐺 🐶 🐷=====╗");
            printf("\n               ║                                 ║");
            printf("\n               ║      LIST MENU:                 ║");
            printf("\n               ║                                 ║");
            printf("\n               ║  m - print menu                 ║");
            printf("\n               ║  p - print list                 ║");
            printf("\n               ║  c - print list current         ║");
            printf("\n               ║                                 ║");
            printf("\n               ║  h - go to head                 ║");
            printf("\n               ║  n - go to next                 ║");
            printf("\n               ║                                 ║");
            printf("\n               ║  a - add head                   ║");
            printf("\n               ║  s - add next                   ║");
            printf("\n               ║                                 ║");
            printf("\n               ║  x - delete head                ║");
            printf("\n               ║  y - delete next                ║");
            printf("\n               ║  k - kill all list              ║");
            printf("\n               ║                                 ║");
            printf("\n               ║  w - go into next structure 🐾  ║");
            printf("\n               ║  e - exit                       ║");
            printf("\n               ║                                 ║");
            printf("\n               ╚=================================╝");
            printf("\n\n");         
        }

};
#endif