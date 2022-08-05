#include "match.h"

list        *match_primitives = 0;


void        match_start()
{
    if (!match_primitives)
    {
      list_add(&match_primitives, new_match_function(print_int));
      list_add(&match_primitives, new_match_function(skip));
      list_add(&match_primitives, new_match_function(oskip));
      list_add(&match_primitives, new_match_function(call));

     }
}

void        match_end()
{
    list_free(match_primitives, free);
    match_primitives = 0;
}


char    *match(object_list **o, const char **str, ...)
{
    (void) o;
    (void) str;

    char        *r;
    va_list     ap;

    va_start(ap, str);
    r = vmatch(o, str, &ap);    
    va_end(ap);
    return r;
}

char    *vmatch(object_list **o, const char **str, va_list *ap)
{
    match_ctx ctx = {*o, *str, 0};
    vva_lisp(&match_primitives, &ctx, ap);
    *o = ctx.o;
    *str = ctx.str;
    return ctx.output;
}