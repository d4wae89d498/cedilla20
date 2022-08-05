#include "match.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
list        *match_primitives = 0;

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

typedef int    (*match_function)(list **primitives, match_ctx*ctx, va_list *ap);

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

int main()
{
    match_start();

    const char *str = " 2 2  (4 + (9 * 8))";
    object_list *o = 0;
    match(&o, &str, 
        "print_int",    10,
      
   //      "print_int",  //  5,
 //       "oskip",         is_space,
 //       "oskip",        is_digit,
        "skip",         is_space,  
        "skip",     is_digit,
        "call",     print_str,
   //     "call2", print_str,
        "skip", is_space, 

    "");

    match_end();
}
