#include "cedilla.h"

char *cedilla_macro_4(char **src, parser_ctx *ctx) { 
    if (!strncmp(*src, "__TEST44__", 10))
    {
        *src += 10;
        return "12";
    }

    if (ctx->is.comments)
    {
        fprintf(stderr, "comments %c [%.10s][%s] %i\n", **src, *src,"42", strncmp(*src, "42", 9));
        if (!strncmp(*src, "42", 10))
        {
            printf("-\n");
        }
    }
    if (ctx->is.comments && !strncmp(*src, "42", 10))
    {
        *src += 10;
        return "12";
    }
    return (0);
 }
