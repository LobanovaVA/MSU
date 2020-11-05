#ifndef LIST_H
#define LIST_H

#include "list_node.h"
#include "hash.h"
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

    int read (FILE *fp, hash& hah_set);


    int insert (char *buf, int ph, int gr, hash& hah_set);

    void print (FILE* out = stdout);


    int do_command(command &line, hash& hah_set);
    int search(list_node *curr, command &line);
    int like(char *str_name, char *str_like);





};
#endif


