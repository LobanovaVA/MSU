#ifndef COMMAND
#define COMMAND

#include "record.h"

class list_node;

class command: public record
{
private:
    cmd_type type = CMD_NONE;
    cond_type c_name  = COND_NONE;
    cond_type c_phone = COND_NONE;
    cond_type c_group = COND_NONE;
    op_type oper = OP_NONE;

public:
    friend class data_base;
    friend class group_avl_tree;
    friend class group_avl_tree_node;
    friend int check (list_node *curr, command &line);
    friend int check_group (int gr, command &line);
    command () = default;
   ~command () = default;

    int parse (int *spaces_alph, const char* str = nullptr);
    int arg (char *readed_str, int *pos, int i);
    void print (FILE *out = stdout);
    void print_cmd (FILE *out = stdout);
    void print_arg (FILE *out = stdout);
    void print_arg_debug (FILE *out = stdout);

};

#endif
