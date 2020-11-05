#ifndef HASH_H
#define HASH_H

#include "hash_node.h"

class hash
{
private:
    hash_node **arr = nullptr;
    int size = 0;

public:
    friend class data_base;
    hash (int n = 0) { size = n; arr = new hash_node *[n]; for (int i = 0; i < size; i++) arr[i] = nullptr;}
    ~hash () { delete_hash(); arr = nullptr; }

    void set_size (int n = 0)
    {
    	delete_hash();
    	size = n;
    	arr = new hash_node *[n]; 
    	for (int i = 0; i < size; i++) arr[i] = nullptr;
    }

    void print (FILE* out = stdout)
    {
        for (int i = 0; i < size; i++)
        {
            fprintf(out, "arr[%5d]:\n", i);
            hash_node *curr = arr[i];
            int j = 0;
            while(curr && j<MAX_PRINT)
            {
                if (curr -> orig)  {  curr -> orig -> print (out);}
                curr = curr -> next;
                j++;
            }
        }
    }


    int insert (list_node *elem)
    {
    	hash_node *elem_h;
	    elem_h = new hash_node;
	    if (!elem_h) return delete elem_h, ERROR_NOT_ENOUGH_MEMORY; 
	    elem_h -> orig = elem;

	    int p = name_hash (elem -> get_name(), size);
	    hash_node *tmp = arr[p];
	    if (!tmp) arr[p] = elem_h;
	    else
	    {
	        elem_h -> next = tmp;
	        tmp -> prev = elem_h;
	        arr[p] = elem_h;
	    }
	    return 0;
    }


    void delete_current (list_node *curr)
    {
        if (!curr) return;
        int n = name_hash (curr -> get_name(), size);
        hash_node *curr_h = arr[n];

        while (curr_h && curr_h -> orig != curr) curr_h = curr_h -> next;
        if (!curr_h) return;

        if (curr_h == arr[n]) arr[n] = curr_h -> next;
        if (curr_h -> next) curr_h -> next -> prev = curr_h -> prev;
        if (curr_h -> prev) curr_h -> prev -> next = curr_h -> next;
        delete curr_h;
    }

    void delete_hash () 
    { 
        for (int i = 0; i < size; i++)
        {
            hash_node *tmp = arr[i], *ptr;
            while (tmp)
            {
                ptr = tmp -> next;
                delete tmp;
                tmp = ptr;
            }
        }
        if (arr) delete[] arr;
        size = 0;
    }


    list_node * search (hash_node *curr_h, command &line)
    {
        hash_node *curr, *head_found = nullptr;
        for (curr = curr_h; curr; curr = curr -> next)
            if (strcmp (curr -> orig -> get_name(), line.get_name()) == 0)
                if (check (curr -> orig, line)) 
                    { head_found = curr; break; }
            
        if (!head_found) return nullptr;
        list_node *curr_found = head_found -> orig;
        curr -> orig -> next_found = nullptr;

        for (curr = head_found -> next; curr; curr = curr -> next)
            if (strcmp (curr -> orig -> get_name(), line.get_name()) == 0)
                if (check (curr -> orig, line)) 
                { 
                    curr_found -> next_found = curr -> orig;
                    curr_found = curr -> orig;
                    curr -> orig -> next_found = nullptr;
                }
        return head_found -> orig;
    }


    list_node * search_or (hash_node *curr_h, command &line, list_node* &res_or)
    {
        hash_node *curr, *head_found = nullptr;
        for (curr = curr_h; curr; curr = curr -> next)
            if (strcmp (curr -> orig -> get_name(), line.get_name()) == 0)
                if (!check (curr -> orig, line)) 
                    { head_found = curr; break; }
            
        if (!head_found) return nullptr;
        list_node *curr_found = head_found -> orig;
        curr -> orig -> next_found = nullptr;

        for (curr = head_found -> next; curr; curr = curr -> next)
            if (strcmp (curr -> orig -> get_name(), line.get_name()) == 0)
                if (!check (curr -> orig, line)) 
                { 
                    curr_found -> next_found = curr -> orig;
                    curr_found = curr -> orig;
                    curr -> orig -> next_found = nullptr;
                }
        res_or = curr_found;
        return head_found -> orig;
    }

};

#endif


