#include "match.h"

int str_is(match_ctx *ctx, va_list ap)
{
    char *str;

    str = va_arg(ap, char *);
    return !strncmp(ctx->str, str, strlen(str)) ? strlen(str) : 0;
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
