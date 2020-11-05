#ifndef DATA_BASE
#define DATA_BASE

#include "list.h"
#include "hash.h"
#include "avl_tree.h"

class data_base
{
private:
    hash search1;
    avl_tree *search2 = nullptr;
    list conteiner;
    int size1 = 0;
    int size2 = 0;
public:
    data_base () = default;
   ~data_base () { delete[] search2; size1 = size2 = 0; }

    data_base (int n1 = 0, int n2 = 0) 
    { 
    	size1 = n1;
    	size2 = n2;
    	search1.set_size (size1);
    	search2 = new avl_tree [size2];
    }

    int read (FILE *fp);
    void print (FILE* out = stdout); 

    int insert (char *buf, int ph, int gr);
    list_node * select (command &line);

    int do_command(command &line);
    void print_select (list_node *res);
    void delete_select (list_node *res);
    int cheack(list_node *curr, command &line);

};

#endif
