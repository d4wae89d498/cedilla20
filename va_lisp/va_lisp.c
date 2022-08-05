#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "va_lisp.h"

int vva_lisp(list **lst, void *data, va_list *ap)
{
    list *it;
    named_va_function *named_function;
    char *name;

    long long r;

    it = *lst;
    if (!it)
        return 0;
    r = 0;
    while (1)
    {
        new_keyword: 
        it = *lst;
        if (!it)
            return 0;
        name = (char *)va_arg(*ap, char *);
        if (!name || !name[0])
            return 0;
        while (it)
        {
            named_function = (named_va_function *)it->data;
            if (name == named_function->name || !strcmp(name, named_function->name))
            {
                printf("[va_lisp] found function : %s (...)\n", name);
                r = named_function->function(lst, data, ap);
                if (r)
                    return r;
                goto new_keyword;
            }
            else
                it = it->next;
        }
        printf("[va_lisp] function not found : %s (...)\n", name);
        return 0;
    }
}

int va_lisp(list **lst, void *data, ...)
{
    va_list ap;
    int r;

    va_start(ap, data);
    r = vva_lisp(lst, data, &ap);
    va_end(ap);
    return r;
}
