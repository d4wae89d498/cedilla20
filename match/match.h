#ifndef MATCH_H
# define MATCH_H
# include "object_list.h"
# include "stdarg.h"
# include "va_lisp.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

# define match(OBJECT_LIST, STR, ...) _match(OBJECT_LIST, STR, __VA_ARGS__, (long long)0)

typedef struct {
        object_list *o;
        const char  *str;
        char        *output;
    }   match_ctx;
typedef int    (*match_function)( match_ctx*ctx, va_list ap);

char    *_match(object_list **, const char **str, ...);
char    *vmatch(object_list **, const char **str, va_list);
// PRIMITIVES :
int     print_int( match_ctx*ctx, va_list ap);
int     is_digit( match_ctx*ctx, va_list ap);
int     is_space( match_ctx*ctx, va_list ap);
int     print_str( match_ctx*ctx, va_list ap);
//int     call( match_ctx*ctx, va_list ap);
int     skip ( match_ctx*ctx, va_list ap);
int     oskip ( void*data, va_list ap);
int     capture ( void*data, va_list ap);
int     cappture ( void*data, va_list ap);

#endif