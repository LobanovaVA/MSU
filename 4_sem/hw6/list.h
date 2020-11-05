#ifndef LIST_H
#define LIST_H

#include "list_node.h"

class list
{
private:
    list_node *head = nullptr;

public:
    friend class data_base;
    list () = default;
    ~list () { delete_list(); head = nullptr; }

    void delete_list () { while (head) delete_head(); }
    void delete_head ();
    void delete_current (list_node *curr);

    void print (FILE* out = stdout);

    int insert (list_node *elem);
    list_node * search (command &line);

};
#endif


