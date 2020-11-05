#ifndef LIST_H
#define LIST_H

#include "list_node.h"

class list
{
private:
    list_node *head = nullptr;
    list_node *head_found = nullptr;

public:
    friend class data_base;
    list () = default;
    ~list () { delete_list(); head = nullptr; }

    void delete_list () { while (head) delete_head(); }
    void delete_head ();
    void delete_current (list_node *curr);

    void print (FILE* out = stdout);

    int insert (list_node *elem);
    void  search (command &line, list_node *&head_found);


    //SORT
    bool cmp (list_node *x, list_node *y, command &line);
    bool add_head (list_node *elem);
    bool add_before_head (list_node *elem);
    list_node * cut_next (list_node *current);
    void insert_sort (list_node *j, list_node *i);
    void linear_insertion_sort (command &line);


    list_node * merge (list_node *cur_head, size_t k, list_node * & last, command &line);
    void Neuman_sort (command &line);

};
#endif


