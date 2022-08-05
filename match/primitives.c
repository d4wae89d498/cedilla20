#include "match.h"

int   print_int( match_ctx*ctx, va_list ap)
{
    (void) ap;
    (void) ctx;

    printf("print int\n");
    printf("%lli\n", va_arg(ap, long long ));
    return 0;
}


int   is_digit( match_ctx*ctx, va_list ap)
{
    (void) ap;


    int i = 0;
    while( (ctx->str[i]) >= '0' && ctx->str[i] <= '9')
    {
        i += 1;
    }
    printf("SKIPPED: %i\n", i);
    return i;
}

int   is_space( match_ctx*ctx, va_list ap)
{
    (void) ap;


    int i = 0;
    while(isspace(ctx->str[i]))
    {
        i += 1;
    }
    printf("SKIPPED: %i\n", i);
    return i;
}

int   print_str( match_ctx*ctx, va_list ap)
{
    (void) ap;


    printf("STR: %s\n", ctx->str);
    return 0;
}


int   call( match_ctx*ctx, va_list ap)
{
    (void) ap;


    printf("call\n");
    match_function f = va_arg(ap, match_function);
    return f( ctx, ap);
}




int  skip ( match_ctx*ctx, va_list ap)
{
    match_function    f = va_arg(ap, match_function);
    int         r = 0;
    printf("skipping...\n");
    r = f( ctx, ap);
    if (!r)
        return 1;
    ctx->str += r;
    return 0;
}

int   oskip ( void*data, va_list ap)
{
        printf("oo skipping...\n");
    skip( data, ap);
    return 1;
}
