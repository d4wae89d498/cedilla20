#include "cedilla.h"

char *cedilla_macro_0(macro_list **macros, char **src, parser_ctx *ctx) { 
    if (**src == '"')
    {
        if (ctx_is_code(*ctx))
            ctx->is.str = 1;
        else if (ctx->is.str)
            ctx->is.str = 0;
    }
    if (**src == '\'')
    {
        if (ctx_is_code(*ctx))
            ctx->is.chr = 1;
        else if (ctx->is.chr)
            ctx->is.chr = 0;
    }
    if (**src == '/' && *(*src + 1) == '/')
    {
        if (ctx_is_code(*ctx))
            ctx->is.comment = 1;
    }
    if (**src == '/' && *(*src + 1) == '*')
    {
        if (ctx_is_code(*ctx))
            ctx->is.comments = 1;
    }
    if (**src == '*' && *(*src + 1) == '/')
    {
        if (ctx->is.comments)
            ctx->is.comments = 0;
    }
    if (**src == '\n')
    {
        ctx->is.comment = 0;
        ctx->is.str = 0;
        ctx->is.chr = 0;
    }
    if (ctx_is_code(*ctx))
    {
        if (**src == '(')
            ctx->levels.parentheses += 1;
        if (**src == '[')
            ctx->levels.brackets += 1;
        if (**src == '{')
            ctx->levels.braces += 1;
        if (**src == ')')
            ctx->levels.parentheses -= 1;
        if (**src == ']')
            ctx->levels.brackets -= 1;
        if (**src == '}')
            ctx->levels.braces -= 1;
    }
    return (0);
 }
