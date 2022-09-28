#include "compiler.h"
#define main main4242
#undef IDE_COMPAT
#define IDE_COMPAT 0
char *cedilla_macro_1(compiler_ctx *ctx, char **src)
{
(void) ctx;
(void) src;
#line 24 "spec/core_syntax.ç"

    if (!strncmp(*src, "__G1__", 6))
    {
        *src += 6;
        return strdup("41");     
    }
    return 0;

}
