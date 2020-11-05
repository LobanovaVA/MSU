#ifndef PARSER
#define PARSER

#include <stdio.h>
#include <string.h>
#include "addition.h"
#include "operation.h"

class operation;

class parser
{
private:
    char orig_str [LEN];
    char parser_str [LEN];
    int  lens[LEN] = {0};
    int  pos[LEN] = {0};

public:
    friend class operation;
    ~parser () = default;
    parser () = default;
    parser ( int* alph, char *readed_str = nullptr) { init (alph ,readed_str); }

    int init ( int* alph, char *readed_str = nullptr);
    void print();
};

#endif
