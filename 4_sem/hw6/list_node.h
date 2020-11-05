#ifndef LIST_NODE_H
#define LIST_NODE_H

#include "record.h"
#include "command.h"

class list_node: public record
{
private:
    list_node *next = nullptr;
    list_node *prev = nullptr;
    list_node *next_found = nullptr;
public:
    friend class list;
    friend class hash;
    friend class avl_tree;
    friend class data_base;
    list_node () = default;
    ~list_node () = default;

};

#endif

