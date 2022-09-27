#include "compiler.h"
#define main main4242
#undef IDE_COMPAT
#define IDE_COMPAT 0
char *cedilla_macro_1(macro_list **macros, char **src, compiler_ctx *ctx) { 
    if (!strncmp(*src, "__G1__", 6) && !ctx->is.str)
    {
        *src += 6;
        return "41";     
    }
    return 0;
 }
