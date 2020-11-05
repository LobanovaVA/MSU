#ifndef HASH_H
#define HASH_H

#include "hash_node.h"

int name_hash (char *str, int n);

class list;
class hash
{
private:
    hash_node **arr = nullptr;
    int size = 0;

public:
    friend class list;
    hash (int n = 0) { size = n; arr = new hash_node *[n]; for (int i = 0; i < size; i++) arr[i] = nullptr;}
    ~hash () { delete_hash(); arr = nullptr; }

    void delete_hash () 
    { 
        for (int i = 0; i< size; i++)
        {
            hash_node *tmp = arr[i], *ptr;
            while (tmp)
            {
                ptr = tmp -> next;
                delete tmp;
                tmp = ptr;
            }
        }

        delete[] arr;
        size = 0;
    }

    void delete_current (hash_node *curr)
    {

        if (!curr) return;
        //curr -> orig = nullptr;
        if (curr -> next) curr -> next -> prev = curr -> prev;
        if (curr -> prev) curr -> prev -> next = curr -> next;
        delete curr;
    }









    //int read (FILE *fp);

    //int insert (char *buf, int ph, int gr);

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






};





#endif


