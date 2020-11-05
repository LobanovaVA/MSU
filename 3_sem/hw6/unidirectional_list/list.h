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
		~list () { delete_list();}

		void delete_list ();
		int read (FILE *);
        void print(FILE *out=stdout);      

//navigation:
        list_node * get_current () const { return current; }
        list_node * get_head () const { return head; }
        list_node * get_next () const { if (current) return current -> next; else return nullptr; } 
        list_node * get_tail (list_node * tmp) const 
        { 
                while (tmp && tmp -> next)
                        tmp = tmp -> next;
                return tmp; 
        } 

        void go_head () { current = head; }
        bool go_next () { if (current) return current = current -> next,  true; else return false; }
        
//adding:

        bool add_head (list_node *elem) 
        { 
                if (head || !elem) return false; 
                head = elem;
                head -> next = nullptr;
                current = head;
                return true; 
        }
        bool add_next (list_node *elem)
        { 

                if ( (current && current -> next) || !elem) return false; 
                if (head == nullptr) return add_head(elem);
                current -> next = elem;
                current -> next -> next = nullptr;
                current = current -> next;
                return true; 
        }

        bool add_before_head (list_node *elem)
        { 

                if (!elem) return false; 
                if (head == nullptr) return add_head(elem);

                list_node *tmp = head;

                head = elem;
                head -> next = tmp;
                current = head;
                return true; 
        }

//cut:

        list_node * cut_head ()
        {
                list_node *tmp = head;
                if (head) 
                {
                        head = tmp -> next;
                        return tmp;
                }
                return nullptr;
        }

        list_node * cut_next ()
        {
                if (current) 
                {
                        list_node *tmp = current -> next;
                        if (tmp)
                        {
                                current -> next = tmp -> next;
                                return tmp;
                        }
                }
                return nullptr;
        }
        
//deleting:
        void delete_head ()
        {
                list_node *tmp = head;
                if (head) 
                        {
                                head = tmp -> next;
                                delete tmp;
                        }
        }

        void delete_next ()
        {
                if (current) 
                {
                        list_node *tmp = current -> next;
                        if (tmp)
                        {
                                current -> next = tmp -> next;
                                delete tmp;
                        }
                }
        }

//sort:
        void bubble_sort (bool (*cmp)(list_node*, list_node*));
        void min_elem_sort (bool (*cmp)(list_node*, list_node*));
        void max_elem_sort (bool (*cmp)(list_node*, list_node*));

        void linear_insertion_sort (bool (*cmp)(list_node*, list_node*));
        void insert (list_node *, list_node *);

        void Neuman_sort (bool (*cmp)(list_node*, list_node*));
        list_node * merge (list_node *, size_t k, list_node * & , bool (*cmp)(list_node *, list_node *));

        void quick_sort (bool (*cmp)(list_node*, list_node*)){  _quick_sort(head, nullptr, cmp); }
        void _quick_sort (list_node *first, list_node *end, bool (*cmp)(list_node *, list_node *));

        //void quick_sort (bool (*cmp)(list_node*, list_node*));

//other:
        bool is_empty () { return !head; }
        int length();
        bool sort_control (bool (*cmp)(list_node* x, list_node* y));
        
};
#endif
