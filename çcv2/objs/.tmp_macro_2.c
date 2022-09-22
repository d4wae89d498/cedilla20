#include "cedilla.h"
#define main main4242
#undef IDE_COMPAT
#define IDE_COMPAT 0
char *cedilla_macro_2(macro_list **macros, char **src, parser_ctx *ctx) { 
    if (!strncmp(*src, "__G2__", 6) && !ctx->is.str)
    {
        *src += 6;
        return strdup((char[7]) {'_', '_', 'G', '1', '_', '_', 0});     
    }
    return 0;
 }
