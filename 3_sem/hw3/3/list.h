#ifndef LIST_H
#define LIST_H

#include "list_node.h"

class list
{
	private:
		list_node *head = nullptr;
		list_node *current = nullptr;

	public:
		list ()  = default;
		~list ();

		void delete_list ();
		int read (FILE *);
                void print(FILE *out=stdout);
                
                list_node * get_head () const { return head; }
                bool is_empty () { return !head; }
                int length();
                
                list_node* solve_1 (student& s);
                list_node* solve_2 (int k);
                list_node* solve_3 ();
                list_node* solve_4 ();
                list_node* solve_5 (int k);
                list_node* solve_6 ();
                list_node* solve_7 ();
                list_node* solve_8 (int k);
                list_node* solve_9 (list_node *head_b);
        
};
#endif
