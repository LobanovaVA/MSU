#ifndef LIST_H
#define LIST_H

#include "addition.h"
#include "list_node.h"
#include "command.h"


class list
{
private:
    list_node *head = nullptr;

public:
    list () = default;
    ~list () { delete_list(); head = nullptr; }

    void delete_list () { while (head) delete_head(); }
    void delete_head ();
    void delete_current (list_node *curr);

    int read (FILE *fp);


    int insert (char *buf, int ph, int gr);

    void print (FILE* out = stdout);


    int do_command(command &line);
    int search(list_node *curr, command &line);




};
#endif


