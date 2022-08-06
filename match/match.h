#ifndef MATCH_H
# define MATCH_H
# include "object_list.h"
# include "stdarg.h"
# include "va_lisp.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

# define match(CTX, ...) _match(CTX, __VA_ARGS__, (long long)0)

typedef struct {
        object_list *o;
        char        *str;
        char        *output;
    }   match_ctx;

typedef char    *(*macro_function)(match_ctx *ctx); 
typedef int     (*match_function)(match_ctx *ctx, va_list ap);

char    *_match(match_ctx *ctx, ...);
char    *vmatch(match_ctx *ctx, va_list);
// primitives.c
int     skip ( match_ctx*ctx, va_list ap);
int     oskip ( match_ctx*data, va_list ap);
int     capture ( match_ctx*data, va_list ap);
int     parse(match_ctx *ctx, va_list ap);
int     print_int( match_ctx*ctx, va_list ap);
int     print_str( match_ctx*ctx, va_list ap);
// is.c
int     is_digit( match_ctx*ctx, va_list ap);
int     is_space( match_ctx*ctx, va_list ap);
int     is_digit( match_ctx*ctx, va_list ap);
int     str_is( match_ctx*ctx, va_list ap);



#endif