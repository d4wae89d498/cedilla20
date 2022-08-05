#include "match.h"

list        *match_primitives = 0;


char    *_match(object_list **o, const char **str, ...)
{
    (void) o;
    (void) str;

    char        *r;
    va_list     ap;

    va_start(ap, str);
    r = vmatch(o, str, ap);    
    va_end(ap);
    return r;
}

char    *vmatch(object_list **o, const char **str, va_list ap)
{
    match_ctx ctx = {*o, *str, 0};
    vva_lisp(&ctx, ap);
    *o = ctx.o;
    *str = ctx.str;
    return ctx.output;
}