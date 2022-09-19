#include "cedilla.h"

char *cedilla_macro_2(macro_list **macros, char **src, parser_ctx *ctx) { 
    if (ctx->is.str && !strncmp(*src, "__TEST21__", 10))
    {
        *src += 10;
        return "42";
    }
    if (ctx->is.comment && !strncmp(*src, "__TEST44__", 10))
    {
        *src += 10;
        return "21";
    }
    if (ctx->is.comments && !strncmp(*src, "__TEST41__", 10))
    {
        *src += 10;
        return "12";
    }
    return (0);
 }
