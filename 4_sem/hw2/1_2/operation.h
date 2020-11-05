#ifndef OPERATION
#define OPERATION

#include <stdio.h>
#include <string.h>
#include "addition.h"

class parser;

class operation
{
private:
    char *given_str  = nullptr;
    int space_alph[256] = {0};

public:
    friend class parser;
    operation () = default;
    operation (const char *spaces_str = nullptr, char *str = nullptr) { init (spaces_str, str); }
    ~operation () = default;

    int init (const char *spaces_str, char *str = nullptr);
    void print();
    int * get_space_alph () { return space_alph; }

    int check_one_word (char *readed_str, parser* S);
    int solve_1 (const char *a, const char *b, parser* S);

    int check_all_words (char *readed_str, parser* S);
    int solve_2 (const char *a, const char *b, parser* S);
};

#endif
