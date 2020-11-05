#ifndef HASH_NODE_H
#define HASH_NODE_H

#include "list_node.h"

class hash_node
{
private:
    list_node *orig = nullptr;
    hash_node *next = nullptr;
    hash_node *prev = nullptr;
public:
    friend class hash;
    friend class group_avl_tree_node;
    hash_node () = default;
    ~hash_node () = default;
};

#endif
