#ifndef LIST_NODE_H
#define LIST_NODE_H

//#include "addition.h"
#include "record.h"

class list;

class list_node: public record
{
private:
    list_node *next = nullptr;
    list_node *prev = nullptr;
public:
    friend class list;
    list_node () = default;
    ~list_node () = default;

    list_node * get_next (list_node *curr) const
    {
        if (curr) return curr -> next;
        else return nullptr;
    }
    list_node * get_prev (list_node *curr) const
    {
        if (curr) return curr -> prev;
        else return nullptr;
    }

};

#endif

