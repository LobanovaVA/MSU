#ifndef HASH_NODE_H
#define HASH_NODE_H

//#include "addition.h"
#include "list_node.h"

class hash;
class list;


class hash_node
{
private:
    list_node *orig = nullptr;
    hash_node *next = nullptr;
    hash_node *prev = nullptr;
public:
    friend class hash;
    friend class list;
    hash_node () = default;
    ~hash_node () = default;


};

#endif
