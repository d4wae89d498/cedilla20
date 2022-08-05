#ifndef VA_LISP_H
# define VA_LISP_H
#include "../list/list.h"
#include <stdarg.h>
typedef int(*va_function)(list **primitives, void *data, va_list *ap);
int    vva_lisp(list **lst, void *data, va_list *ap);
int    va_lisp(list **lst, void *data, ...);
typedef struct 
{
    char  *name;
    va_function function; 
}   named_va_function;

#define new_va_function(F) ({                                           \
    named_va_function*  ptr = malloc(sizeof(named_va_function));        \
    *ptr = (named_va_function) {#F,F};                                  \
    ptr;                                                                \
})
#define lisp(A, B, ...) va_lisp(A, B, __VA_ARGS__, "")
#endif