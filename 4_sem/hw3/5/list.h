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
        bool is_empty () {	return !head; }

        void solve_1 (student& s);
        void solve_2 (int k);
        void solve_3 ();
        void solve_4 ();
        void solve_5 (int k);
        void solve_6 ();
        void solve_7 ();
        void solve_8 (int k);
        
};
#endif
