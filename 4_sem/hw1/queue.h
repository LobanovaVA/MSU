#ifndef QUEUE_H
#define QUEUE_H

#include "queue_node.h"

template <class T, template <class> class T1, template <class, template <class> class> class T2>
class queue
{
	private:
		typedef queue_node <T, T1, T2> queue_node_T;
		queue_node_T *head = nullptr;
		queue_node_T *tail = nullptr;
		enum MENU_ITEMS
		{
			MENU_MENU 		= 'm',
			MENU_PRINT 		= 'p',
            MENU_CURRENT    = 'c',
			MENU_ADD 		= 'a',
			MENU_DEL	 	= 'd',
			MENU_KILL 		= 'k',
			MENU_WORK 		= 'w',
			MENU_EXIT 		= 'e'
		};

	public:
		queue () = default;
		~queue () { delete_queue (); head = tail = nullptr; }

		void delete_queue (){ while (head) pop_head(); }

		int read (FILE *fp, int n3, int n2, int n1)
		{
			int ret;
			delete_queue ();
			queue_node_T *elem;
			for (int i = 0; i < n3; i++)
			{
				elem = new queue_node_T;
				if (!elem) return ERROR_NOT_ENOUGH_MEMORY;
				ret = elem -> read (fp, n2, n1);
		                if (ret < 0) return delete elem, ret;
				if (ret > 0) return delete elem, ERROR_NOT_ENOUGH_DATA;
				push_tail(elem); 
			}
			return 0;

		}

        void print(FILE *out = stdout)
		{
		    int i=0; 
		    queue_node_T *curr = head;
		    while(curr && i<MAX_PRINT)
		    {	
		        curr -> print (out);
		        curr = curr -> next;
		        i++;
		    }
		}

		void push_tail (queue_node_T *elem = nullptr)
		{
			if (!elem) elem = new queue_node_T;
			if (is_empty ()) head = tail = elem; 
			else 
			{
		                tail -> next = elem;
				tail = elem ;
			}
		}

		void pop_head ()
		{
			if (!is_empty ())
			{
		                queue_node_T *new_head = head -> next;
				delete head;
				head = new_head;
			}
		}


		queue_node_T * get_head () const { return head; }
		
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
                    case MENU_MENU		: {printf("PRINT QUEUE MENU:");				print_menu (); break;}
                    case MENU_PRINT		: {printf("PRINT QUEUE:\n");				print (); break;}
                    case MENU_CURRENT	: {printf("PRINT QUEUE HEAD:\n");			if (head) head -> print (); break;}
                    case MENU_ADD		: {printf("ADD ELEM (PUSH_TAIL)\n");		push_tail (); break;}
                    case MENU_DEL 		: {printf("DELETE ELEM (POP HEAD)\n");      pop_head (); break;}
                    case MENU_KILL		: {printf("KILL ALL QUEUE\n");				delete_queue (); break;}
                    case MENU_WORK		: {printf("GO INTO NEXT STRUCTURE (LIST)\n");	if (head) head -> menu (); break;}
					case MENU_EXIT		: return;
				}
		    }
		}


		void print_menu()
		{
			printf("\n\n");
	        printf("\n               ╔=====🐙 🐯 🐰 🐲 🐢 🐺 🐶 🐷=====╗");
	        printf("\n               ║                                 ║");
	        printf("\n               ║      QUEUE MENU:                ║");
	        printf("\n               ║                                 ║");
	        printf("\n               ║  m - print menu                 ║");
	        printf("\n               ║  p - print queue DEBUG          ║");
	        printf("\n               ║  c - print queue head           ║");
	        printf("\n               ║                                 ║");
	        printf("\n               ║  a - add to tail                ║");
	        printf("\n               ║                                 ║");
	        printf("\n               ║  d - pop head                   ║");
	        printf("\n               ║  k - kill all queue 🔫          ║");
	        printf("\n               ║                                 ║");
	        printf("\n               ║  w - go into next structure 🐾  ║");
	        printf("\n               ║  e - exit                       ║");
	        printf("\n               ║                                 ║");
	        printf("\n               ╚=================================╝");
			printf("\n\n");			
		}


};
#endif
