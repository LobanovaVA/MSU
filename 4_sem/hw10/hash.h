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
    friend class group_avl_tree_node;
    hash (int n = 0) { size = n; arr = new hash_node *[n]; for (int i = 0; i < size; i++) arr[i] = nullptr;}
    ~hash () { delete_hash(); arr = nullptr; }

    void set_size (int n = 0)
    {
    	delete_hash();
    	size = n;
    	arr = new hash_node *[n]; 
    	for (int i = 0; i < size; i++) arr[i] = nullptr;
    }

    void print (int space = 0, FILE* out = stdout)
    {
        fprintf(out, "\n");
        for (int i=0; i<space-1; i++) fprintf (out, "        ");
        fprintf(out, "LIST_HASH:\n");
        for (int i = 0; i < size; i++)
        {
            for (int i=0; i<space-1; i++) fprintf (out, "        ");
            fprintf(out, "arr[%2d]:\n", i);
            hash_node *curr = arr[i];
            int j = 0;
            while(curr && j<MAX_PRINT)
            {
                for (int i=0; i<space-1; i++) fprintf (out, "        ");
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


    void search (hash_node *curr_h, command &line, list_node *&head_found)
    {
        hash_node *curr;
        for (curr = curr_h; curr; curr = curr -> next)
            if (strcmp (curr -> orig -> get_name(), line.get_name()) == 0)
                if (check (curr -> orig, line)) 
                { 
                    curr -> orig -> next_found = head_found; 
                    head_found = curr -> orig;
                }
        return;
    }


    void search_or (hash_node *curr_h, command &line, list_node *&head_found)
    {
        hash_node *curr;
        for (curr = curr_h; curr; curr = curr -> next)
            if (strcmp (curr -> orig -> get_name(), line.get_name()) == 0)
                if (!check (curr -> orig, line)) 
                { 
                    curr -> orig -> next_found = head_found; 
                    head_found = curr -> orig;
                }
        return;
    }

};

#endif