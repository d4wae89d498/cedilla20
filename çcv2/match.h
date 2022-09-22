#include "cedilla.h"

typedef int (*until)(macro_list **macros, parser_ctx *ctx, char **str);

#define parse(...)   _parse(macros, ctx, src, __VA_ARGS__)
int     _parse(macro_list **l, parser_ctx *ctx, char **src, char *str)
{
    int r;

    r = try_apply_macros(l, &str, ctx);
    if (r == strlen(str))
        return (r);
    return (0);
}

#define issep()      _issep(macros, ctx, src) 
int     _issep(macro_list **l, parser_ctx *ctx, char **src)
{
    int r;

    r = 0;
    while (**src)
        if (isspace(**src))
            r += 1;
        else
            return (r);
    return (r);
}

#define skip(...)   _skip(macros, ctx, src, __VA_ARGS__)
int     _skip(macro_list **l, parser_ctx *ctx, char **src, int n)
{
    return cursor_incr(src, ctx, n);
}

#define isstr(...)   _isstr(macros, ctx, src, __VA_ARGS__)
int     _isstr(macro_list **l, parser_ctx *ctx, char **src, char *str)
{
    int sl;

    sl = strlen(str);
    if (!strncmp(*src, str, sl))
    {
        return sl;
    }
    return (0);
}

#define capture(...)   _capture(macros, ctx, src, __VA_ARGS__)
int     _capture(macro_list **l, parser_ctx *ctx, char **src, char **buffer, until stop)
{
    int cl = 0;

    *buffer = "";
    while (*(*src + cl))
    {
        if (stop(l, ctx, src + cl))
        {
            return (cl);
        }
        asprintf(buffer, "%s%c", *buffer, *(*src + cl));
        cl += 1;
    }
    *buffer = 0;
    return (0);
}

macro_list     *macro_add(macro_list **l, macro_list *v)
{
    macro_list  *it;

    if (!*l)
    {
        *l = malloc(sizeof(macro_list));
        if (!*l)
            return 0;
        (*l)->next = 0;
        (*l)->item = v->item;
        return *l;
    }
    it = *l;
    while (it)
    {
        if (!it->next)
        {
            it->next = malloc(sizeof(macro_list));
            if (!it->next)
                return (0);
            it->next->item = v->item;
            it->next->next = 0;
            return (it->next);
        }
        it = it->next;
    }
    return (0);
}

#define cedilla_match_end -4242
#define match(...)   _match(macros, ctx, src, __VA_ARGS__, cedilla_match_end)
int _match(macro_list **macros, parser_ctx *ctx, char **src, ...)
{
    macro_list  *new_macros;
    macro_list  *it;
    parser_ctx  new_ctx;
    char        *new_src;
    va_list     ap;
    int         n;
    int         total_n;

    new_macros = 0;
    it = *macros;
    while (it)
    {
        macro_add(&new_macros, it);
        // todo: catch alloc error
        it = it->next;
    }
    new_src = *src;
    // todo: impl & clone ctx dynamic objets
    new_ctx = *ctx;
    total_n = 0;
    va_start(ap, src);
    while (1)
    {
        n = va_arg(ap, int);
        total_n += n;
        if (!n)
        {
            *ctx = new_ctx;
            *src = new_src;
            *macros = new_macros;
            // todo: desrcoy macros, ctx, src 
            return (0);
        }
        else if (n == cedilla_match_end)
        {
            // todo: desrcoy new_*
            return (total_n);
        }
    }
    va_end(ap);
}
