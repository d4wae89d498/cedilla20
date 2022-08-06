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
    vva_lisp(ctx, ap);
    return ctx->output;
}