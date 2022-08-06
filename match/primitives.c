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

int   dump_str( match_ctx*ctx, va_list ap)
{
    (void) ap;


    printf("STR: %s\n", ctx->str);
    return 1;
}

char logme(char c)
{

    printf("-- %c\n", c);
    return c;
}

int capture (match_ctx *ctx, va_list ap)
{
    char **str;
    str = va_arg(ap, char **);

 //   printf("withing capture.. [%s]\n", ctx->str);
    match_conditions  c = get_match_conditions(ap, default_conditions);

    printf ("until:: %p\n", c._until);
    printf ("limit:: %d [%s]\n", c._limit, ctx->str);
    printf("\n\n\n");


    return MATCH_COND(str_suffix(str, (char[2]) { logme(ctx->str[i]), 0} ));
  /*  return 
    ({ 
        int i = 0; if (c._limit < 0) c._limit = INT_MAX; 
        while (i < c._limit && ctx->str[i] && ((c._aslong && c._aslong(ctx, ap)) || 1)) 
        { 
         //   printf("capturing .. i = %i\n", i);
            if (!(str_suffix(str, (char[2]) { ctx->str[i], 0} ))) 
                break ; 
            i += 1; 
            if (i >= c._limit || (c._until && c._until(ctx, ap))) 
                break ; 
        } 
        printf (" i = %i\n", i); i;
     });*/

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
    str = va_arg(ap, char *);
    match_conditions  c = get_match_conditions(ap, default_conditions);
    if (!match(ctx, str_is, str, limit, c._limit, until, c._until, aslong, c._aslong))
        return 0;
    match(ctx, skip, eval, str);
    return strlen(str);
}