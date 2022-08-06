#include "match.h"
#include "eval.c"
#include "is.c"

int   print_int( match_ctx*ctx, va_list ap)
{
    (void) ap;
    (void) ctx;

    printf("print int\n");
    printf("%lli\n", va_arg(ap, long long ));
    return 1;
}

int   print_str( match_ctx*ctx, va_list ap)
{
    (void) ap;


    printf("STR: %s\n", ctx->str);
    return 1;
}





int capture (match_ctx *ctx, va_list ap)
{
    (void) ctx;
    (void) ap;
    return 0;
}

int     skip ( match_ctx*ctx, va_list ap)
{
    match_function f =  (void*) va_arg(ap, match_function);

    int         r = 0;
    printf("skipping...\n");
    r = f( ctx, ap);
    if (!r)
        return 0;
    ctx->str += r;
    return 1;
}

int     oskip ( match_ctx*ctx,  va_list ap)
{
    printf("oo skipping...\n");
    skip( ctx, ap);
    return 1;
}

int     parse(match_ctx *ctx, va_list ap)
{
    char *str;
    match_conditions  c = get_match_conditions(ap, default_conditions);

    str = va_arg(ap, char *);
    if (!match(ctx, str_is, str, limit, c._limit, until, c._until, aslong, c._aslong))
        return 0;
    match(ctx, skip, eval, str);
    return strlen(str);
}