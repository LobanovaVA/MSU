#ifndef DATA_BASE
#define DATA_BASE

#include "list.h"
#include "group_avl_tree.h"

class data_base
{
private:
    list conteiner;
    group_avl_tree search3;
    hash search4;
    avl_tree *search5 = nullptr;
    int size1 = 0;
    int size2 = 0;

public:
    friend class list;
    data_base () = default;
   ~data_base () { delete[] search5; size1 = size2 = 0; }

    data_base (int n1 = 0, int n2 = 0) 
    { 
        size1 = n1;
        size2 = n2;
        search3.set_size (n1, n2); 
        search4.set_size (size1);
        search5 = new avl_tree [size2];
    }

    int read (FILE *fp);
    void print (FILE* out = stdout); 

    int insert (char *buf, int ph, int gr);
    
    int do_command(command &line);
    void print_select (list_node *res);
    void print_distinct  (list_node *res, command &line);
    void delete_select (list_node *res);

    list_node * select (command &line);
    //int cheack(list_node *curr, command &line);

};

#endif
