#ifndef MATCH_H
# define MATCH_H
# include "object_list.h"
# include "stdarg.h"
# include "va_lisp.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define new_match_function(F) ({                                           \
    named_va_function*  ptr = malloc(sizeof(named_va_function));        \
    *ptr = (named_va_function) {#F, (void*)F};                                  \
    ptr;                                                                \
})
typedef struct {
        object_list *o;
        const char  *str;
        char        *output;
    }   match_ctx;
typedef int    (*match_function)(list **primitives, match_ctx*ctx, va_list *ap);

char    *match(object_list **, const char **str, ...);
char    *vmatch(object_list **, const char **str, va_list *);
void    match_start();
void    match_end();
// PRIMITIVES :
int     print_int(list **primitives, match_ctx*ctx, va_list *ap);
int     is_digit(list **primitives, match_ctx*ctx, va_list *ap);
int     is_space(list **primitives, match_ctx*ctx, va_list *ap);
int     print_str(list **primitives, match_ctx*ctx, va_list *ap);
int     call(list **primitives, match_ctx*ctx, va_list *ap);
int     skip (list **primitives, match_ctx*ctx, va_list* ap);
int     oskip (list **primitives, void*data, va_list *ap);
int     capture (list **primitives, void*data, va_list *ap);
int     capture (list **primitives, void*data, va_list *ap);
/*
//# define parse     parse,
//... expr
//  until     
//  limit 
//# define call       call,
//... fptr
//# define skip       skip,
// xor
//# define oskip      oskip,
// ... fptr
// until    
// and/or
//limit     
// ... fptr
//# define capture    capture,
// ... fptr
// until    
// limit    
# define _          ,
*/
#endif