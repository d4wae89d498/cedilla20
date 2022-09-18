#include ".macro_cleaner.h"
#ifndef CEDILLA_H
# define CEDILLA_H
# include "libc.h"
# include "sys/mman.h"
# include "ctype.h"
# include "dlfcn.h"
# include "stdio.h"

typedef struct s_parser_ctx
{
    struct 
    {
        int comment:        1;
        int comments:       1;
        int chr:            1;
        int str:            1;
    } is;

    struct {
        int parentheses:    16;
        int brackets:       16;
        int braces:         16;
        int depth:          16;
        int collumns:       16;
        int lines:          16;
    } levels;
} parser_ctx;

typedef char*   macro (char **str, parser_ctx *ctx);

int macro_count = 0;

typedef struct s_macro_list
{
    macro                  *item;
    struct s_macro_list    *next;   
} macro_list;

# define CEDILLA_CONCAT2(X, Y)  X##Y
# define CEDILLA_CONCAT(X, Y)   CEDILLA_CONCAT2(X, Y)
# define CEDILLA_STR2(X)         #X
# define CEDILLA_STR(X)        CEDILLA_STR2(X)
# define CEDILLA_CONCAT2(X, Y)  X##Y
# define CEDILLA_CONCAT(X, Y)   CEDILLA_CONCAT2(X, Y)
# define debugg(...) #__VA_ARGS__
# define each_test(x) , (x + 1)
# define dump_macro(...) printf("[%s:%i dump_macro] %s\n", __FILE__, __LINE__, apply(str, __VA_ARGS__));
# define cdump(...) message(apply(str, __VA_ARGS__))
# define macro CEDILLA_CONCAT(char * cedilla_macro_, __LINE__)(char **str, parser_ctx *ctx)
#endif