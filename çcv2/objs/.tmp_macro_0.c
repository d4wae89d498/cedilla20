#include "cedilla.h"

char *cedilla_macro_0(char **str, parser_ctx *ctx) { 
    if (!strncmp(*str, "__G1__", 6) && !ctx->is.str)
    {
        *str += 6;
        return "41";     
    }
    return 0;
 }
