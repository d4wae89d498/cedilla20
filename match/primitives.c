#include "match.h"

int   print_int(list **primitives, match_ctx*ctx, va_list *ap)
{
    (void) ap;
    (void) ctx;
    (void) primitives;
    printf("print int\n");
    printf("%lli\n", va_arg(*ap, long long ));
    return 0;
}


int   is_digit(list **primitives, match_ctx*ctx, va_list *ap)
{
    (void) ap;
    (void) primitives;

    int i = 0;
    while( (ctx->str[i]) >= '0' && ctx->str[i] <= '9')
    {
        i += 1;
    }
    printf("SKIPPED: %i\n", i);
    return i;
}

int   is_space(list **primitives, match_ctx*ctx, va_list *ap)
{
    (void) ap;
    (void) primitives;

    int i = 0;
    while(isspace(ctx->str[i]))
    {
        i += 1;
    }
    printf("SKIPPED: %i\n", i);
    return i;
}

int   print_str(list **primitives, match_ctx*ctx, va_list *ap)
{
    (void) ap;
    (void) primitives;

    printf("STR: %s\n", ctx->str);
    return 0;
}


int   call(list **primitives, match_ctx*ctx, va_list *ap)
{
    (void) ap;
    (void) primitives;

    printf("call\n");
    match_function f = va_arg(*ap, match_function);
    return f(primitives, ctx, ap);
}




int  skip (list **primitives, match_ctx*ctx, va_list* ap)
{
    match_function    f = va_arg(*ap, match_function);
    int         r = 0;
    printf("skipping...\n");
    r = f(primitives, ctx, ap);
    if (!r)
        return 1;
    ctx->str += r;
    return 0;
}

int   oskip (list **primitives, void*data, va_list *ap)
{
        printf("oo skipping...\n");
    skip(primitives, data, ap);
    return 1;
}
