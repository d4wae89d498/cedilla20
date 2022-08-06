#include "match.h"

#define MATCH_COND(f) ({                                                        \
    int i = 0;                                                                  \
    if (c._limit < 0)                                                           \
        c._limit = INT_MAX;                                                     \
    while (i < c._limit && ctx->str[i] && ((c._aslong && c._aslong(ctx, ap)) || 1))\
    {                                                                           \
        if (!(f))                                                               \
            break ;                                                             \
        i += 1;                                                                 \
        if (i >= c._limit || (c._until && c._until(ctx, ap)))                   \
            break ;                                                             \
    }                                                                           \
    printf (" i = %i\n", i);                                                    \
    i;                                                                          \
})

const match_conditions default_conditions = {-1,0,0};

match_conditions get_match_conditions (va_list ap, match_conditions o)
{
    va_list     apc;
    char        *s;

    va_copy(apc, ap);
    s = va_arg(apc, char *);
    if (s && !strcmp(s, limit))
    {
        (void) va_arg(ap, char*);
        o._limit = va_arg(ap, int);
    }
    va_end(apc);
    va_copy(apc, ap);
    s = va_arg(apc, char *);
    if (s && !strcmp(s, until))
    {
        (void) va_arg(ap, char*);
        o._until = va_arg(ap, match_function);
    }
    va_end(apc);
    va_copy(apc, ap);
    s = va_arg(apc, char *);
    if (s && !strcmp(s, aslong))
    {
        (void) va_arg(ap, char*);
        o._aslong = va_arg(ap, match_function);
    }
    va_end(apc);
    va_copy(apc, ap);
    s = va_arg(apc, char *);
    va_end(apc);
    if (s && (!strcmp(s, aslong) || !strcmp(s, until) || !strcmp(s, limit)))
        return get_match_conditions(ap, o);   
    return o;
} 

int str_is(match_ctx *ctx, va_list ap)
{
    char    *str;
    str = va_arg(ap, char *);
    match_conditions c = get_match_conditions(ap, default_conditions);
    if (c._limit == -1)
        c._limit = strlen(str);
   return MATCH_COND(str[i] != ctx->str[i]);
}

int   is_digit( match_ctx*ctx, va_list ap)
{ 
    match_conditions c = get_match_conditions(ap, default_conditions);
    return MATCH_COND(ctx->str[i] >= '0' && ctx->str[i] <= '9');
}

int   is_space( match_ctx*ctx, va_list ap)
{
    match_conditions c = get_match_conditions(ap, default_conditions);
    return MATCH_COND(isspace(ctx->str[i]));
}
