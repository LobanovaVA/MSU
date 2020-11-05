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
    int cmp = 0;

public:
    friend class parser;
    operation () = default;
    operation (const char *spaces_str = nullptr, char *str = nullptr, const char* x = nullptr) { init (spaces_str, str, x); }
    ~operation () = default;

    int init (const char *spaces_str, char *str = nullptr, const char* = nullptr);
    void print();
    int * get_space_alph () { return space_alph; }

    int solve_4 (const char *a, const char *b, parser* S);
    int check_one_word_cmp1 (char *readed_str, parser* S);
    int check_one_word_cmp2 (char *readed_str, parser* S);
    int check_one_word_cmp3 (char *readed_str, parser* S);
    int check_one_word_cmp4 (char *readed_str, parser* S);
    int check_one_word_cmp5 (char *readed_str, parser* S);
    int check_one_word_cmp6 (char *readed_str, parser* S);


    int solve_5 (const char *a, const char *b, parser* S);
    int check_all_words_cmp1 (char *readed_str, parser* S);
    int check_all_words_cmp2 (char *readed_str, parser* S);
    int check_all_words_cmp3 (char *readed_str, parser* S);
    int check_all_words_cmp4 (char *readed_str, parser* S);
    int check_all_words_cmp5 (char *readed_str, parser* S);
    int check_all_words_cmp6 (char *readed_str, parser* S);
};

#endif
