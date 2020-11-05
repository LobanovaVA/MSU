#ifndef DATA_BASE
#define DATA_BASE

#include "list.h"
#include "group_avl_tree.h"

class data_base
{
private:
    list conteiner;
    group_avl_tree search3;

public:
    data_base () = default;
   ~data_base () = default;

    data_base (int n1 = 0, int n2 = 0) { search3.set_size (n1, n2); }

    int read (FILE *fp);
    void print (FILE* out = stdout); 

    int insert (char *buf, int ph, int gr);
    
    int do_command(command &line);
    void print_select (list_node *res);
    void delete_select (list_node *res);

};

#endif
