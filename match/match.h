#ifndef MATCH_H
# define MATCH_H
# include "object_list.h"
# include "stdarg.h"
# include "va_lisp.h"
# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <limits.h>
# define match(CTX, ...) _match(CTX, __VA_ARGS__, (long long)0)
# define limit "__MATCH_LIMIT__"
# define until "__MATCH_UNTIL__"
# define aslong  "__MATCH_ASLONG__"

int str_suffix(char **str, char *suffix);
int str_prefix(char **str, char *prefix);
typedef struct 
{
    object_list     *o;
    char            *str;
    char            *output;
}   match_ctx;
struct s_conditions; 
typedef char        *(*macro_function)(match_ctx *ctx); 
typedef int         (*match_function)(match_ctx *ctx, va_list ap);
typedef struct s_conditions
{
    int             _limit;
    match_function  _until;
    match_function  _aslong;
} match_conditions;
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