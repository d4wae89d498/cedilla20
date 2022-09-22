#include "cedilla.h"
#define main main4242
#undef IDE_COMPAT
#define IDE_COMPAT 0
char *cedilla_macro_2(macro_list **macros, char **src, parser_ctx *ctx) { 
    char *r;
    if (!strncmp(*src, "__BRACKETS__", 12) && ctx_is_code(*ctx))
    {
        *src += 12;
        asprintf(&r, "%i", ctx->levels.brackets);
        return (r);
    }
    if (!strncmp(*src, "__PARENTHESES__", 15) && ctx_is_code(*ctx))
    {
        *src += 15;
        asprintf(&r, "%i", ctx->levels.parentheses);
        return (r);
    }
    if (!strncmp(*src, "__BRACES__", 10) && ctx_is_code(*ctx))
    {
        *src += 10;
        asprintf(&r, "%i", ctx->levels.braces);
        return (r);
    }
    return (0);
 }
