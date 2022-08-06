#include "match.h"

char    *_match(match_ctx *ctx, ...)
{
    char        *r;
    va_list     ap;

    va_start(ap, ctx);
    r = vmatch(ctx, ap);    
    va_end(ap);
    return r;
}

char    *vmatch(match_ctx *ctx, va_list ap)
{
    int         r;
    object_list *o;
    char        *str;
    char        *output;

    o = olist_clone(ctx->o);
    str = strdup(ctx->str);
    output = strdup(ctx->output);

    r = vva_lisp(ctx, ap);
    if (!r)
    {
        olist_free(ctx->o);
        ctx->o = o;
//        free(ctx->str);
        ctx->str = str; 
        free(ctx->output);
        ctx->output = output;
    }
    else 
    {
        olist_free(o);
        free(str);
        free(output);
    }
    return ctx->output;
}