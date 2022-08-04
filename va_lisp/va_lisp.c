#include <stdarg.h>
#include "../list/list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef long long(*va_function)(list **primitives, void *data, va_list ap);

long long    vva_lisp(list **lst, void *data, va_list ap);

long long   print_5(list **primitives, void*data, va_list ap)
{
    (void) ap;
    (void) data;
    printf("5\n");
    return 0;
}

long long   print_int(list **primitives, void*data, va_list ap)
{
    (void) ap;
    (void) data;
    printf("%i\n", va_arg(ap, int ));
    return 0;
}

long long eval(list **primitives, void*data, va_list ap)
{
    return vva_lisp(primitives, data, ap);
}

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

long long    vva_lisp(list **lst, void *data, va_list ap)
{
    list                *it;
    named_va_function   *named_function;
    char                *name;

    long long           r;

    it = *lst;
    if (!it)
        return 0;
    r = 0;
    while (it)
    {
        name = (char*) va_arg(ap, char*);
        if (!name || !name[0])
            return r;
        named_function = (named_va_function*) it->data;        
        if (!strcmp(name, named_function->name))
        {
            r = named_function->function(lst, data, ap);
            if (r)
                return r;

            it = *lst;
        }
        it = it->next;
    }
    return 0;
}

int    va_lisp(list **lst, void *data, ...)
{
    va_list     ap;
    int         r;

    va_start(ap, data);
    r = vva_lisp(lst, data, ap);
    va_end(ap);
    return r;
}

#define lisp(A, B, ...) va_lisp(A, B, __VA_ARGS__, "")

int main()
{
    list        *lst = 0;
    int         data = 0;


    list_add(&lst, new_va_function(print_5));
    list_add(&lst, new_va_function(print_int));

    lisp(&lst, &data, "print_5", "print_int", 10, "print_int", 10);

    list_free(lst, free);
/*

   list_add(&lst, f);
   

   va_lang(lst, print_5);*/
   // va
}
