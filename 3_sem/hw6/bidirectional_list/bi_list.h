#ifndef BI_LIST_H
#define BI_LIST_H

#include "bi_list_node.h"

class bi_list
{
	private:
		bi_list_node *head = nullptr;
		bi_list_node *current = nullptr;

        public:
		bi_list ()  = default;
		~bi_list () { delete_list();}

		void delete_list ();
		int read (FILE *);
                void print(FILE *out=stdout);      

//navigation:
        bi_list_node * get_current () const { return current; }
        bi_list_node * get_head () const { return head; }
        bi_list_node * get_next () const { if (current) return current -> next; else return nullptr; } 
        bi_list_node * get_prev () const { if (current) return current -> prev; else return nullptr; } 
        bi_list_node * get_tail () const 
        { 
                bi_list_node *tmp = head;
                while (tmp && tmp -> next)
                        tmp = tmp -> next;
                return tmp; 
        } 

        void go_head () { current = head; }
        bool go_next () { if (current) return current = current -> next,  true; else return false; }
        bool go_prev () { if (current) return current = current -> prev,  true; else return false; }

//adding:
        bool add_head (bi_list_node *elem) 
        { 
                if (head || !elem) return false; 
                head = elem;
                head -> next = nullptr;
                head -> prev = nullptr;
                current = head;
                return true; 
        }
        bool add_next (bi_list_node *elem)
        { 

                if ( (current && current -> next) || !elem) return false; 
                if (head == nullptr) return add_head(elem);

/*
                if(!current)
                {       
                        printf("opyat\n");
                        current = head;
                        while (current->next) current = current->next;
                }*/
                

                current -> next = elem;
                current -> next -> next = nullptr;
                current -> next -> prev = current;
                current = current -> next;
                return true; 
        }

        bool add_before_head (bi_list_node *elem)
        { 

                if (!elem) return false; 
                if (head == nullptr) return add_head(elem);

                bi_list_node *tmp = head;

                head = elem;
                head -> next = tmp;
                tmp  -> prev = head;
                head -> prev = nullptr;

                current = head;
                
                return true; 
        }

        bool add_prev (bi_list_node *elem) 
        { 
                if ((current && current -> prev) || !elem) return false; 
                if (current == head) return add_head(elem);

                elem -> next = current;
                elem -> prev = nullptr;
                current -> prev = elem;
                current = current -> prev;
                return true; 
        }
//cut:

        bi_list_node * cut_head ()
        {
                bi_list_node *tmp = head;
                if (head) 
                {
                        head = tmp -> next;
                        if (tmp -> next) tmp -> next -> prev = nullptr;
                        return tmp;
                }
                return nullptr;
        }

        bi_list_node * cut_current ()
        {
                if (current) 
                {
                        bi_list_node *tmp = current;
                        if (current == head) return cut_head();
                        if (tmp -> next) tmp -> next -> prev = tmp -> prev;
                        tmp -> prev -> next = tmp -> next;
                        current = current -> prev;
                        return tmp;    
                }
                return nullptr;
        }
        bi_list_node * cut_next ()
        {
                if (current) 
                {
                        bi_list_node *tmp = current -> next;
                        if (tmp)
                        {
                                current -> next = tmp -> next;
                                if (tmp -> next) tmp -> next -> prev = current;
                                return  tmp;
                        }
                }
                return nullptr;
        }
        bi_list_node * cut_prev ()
        {
                if (current) 
                {
                        bi_list_node *tmp = current -> prev;
                        if (tmp)
                        {
                                current -> prev = tmp -> prev;
                                if (tmp -> prev) tmp -> prev -> next = current;
                                return tmp;
                        }
                }
                return nullptr;
        }




//deleting:

        void delete_head ()
        {
                bi_list_node *tmp = head;
                if (head) 
                {
                        head = tmp -> next;
                        if (tmp -> next) tmp -> next -> prev = nullptr;
                        delete tmp;
                }
        }

        void delete_current ()
        {

                if (current) 
                {
                        if (current == head) return delete_head();
                        if (current -> next) current -> next -> prev = current -> prev;
                        current -> prev -> next = current -> next;
                        bi_list_node *tmp = current;
                        current = current -> prev;
                        delete tmp;    
                }
        }
        void delete_next ()
        {
                if (current) 
                {
                        bi_list_node *tmp = current -> next;
                        if (tmp)
                        {
                                current -> next = tmp -> next;
                                if (tmp -> next) tmp -> next -> prev = current;
                                delete tmp;
                        }
                }
        }
        void delete_prev ()
        {
                if (current) 
                {
                        bi_list_node *tmp = current -> prev;
                        if (tmp)
                        {
                                current -> prev = tmp -> prev;
                                if (tmp -> prev) tmp -> prev -> next = current;
                                delete tmp;
                        }
                }
        }

//sort:
        void bubble_sort (bool (*cmp)(bi_list_node *, bi_list_node *));
        void min_elem_sort (bool (*cmp)(bi_list_node *, bi_list_node *));
        void max_elem_sort (bool (*cmp)(bi_list_node *, bi_list_node *));
        void linear_insertion_sort (bool (*cmp)(bi_list_node *, bi_list_node *));
        void insert (bi_list_node *, bi_list_node *);

        void Neuman_sort (bool (*cmp)(bi_list_node*, bi_list_node*));
        bi_list_node *  merge (bi_list_node *cur_head, size_t k, bi_list_node * & last, bool (*cmp)(bi_list_node *, bi_list_node *));

        void quick_sort (bool (*cmp)(bi_list_node*, bi_list_node*)){  _quick_sort(head, nullptr, cmp); }
        void _quick_sort (bi_list_node *first, bi_list_node *end, bool (*cmp)(bi_list_node *, bi_list_node *));

//other:
        bool is_empty () { return !head; }
        void swap (bi_list_node *, bi_list_node *);

        int length();
        bool sort_control (bool (*cmp)(bi_list_node *, bi_list_node *));
        
        //bi_list_node * partition (bi_list_node *, bi_list_node *, bool (*cmp)(bi_list_node *, bi_list_node *));
        //void _quick_sort (bi_list_node *l, bi_list_node *h, bool (*cmp)(bi_list_node *, bi_list_node *)); 

        
        
};
#endif




