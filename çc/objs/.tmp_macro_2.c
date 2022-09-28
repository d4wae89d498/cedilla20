#include "compiler.h"
#define main main4242
#undef IDE_COMPAT
#define IDE_COMPAT 0
char *cedilla_macro_2(compiler_ctx *ctx, char **src)
{
(void) ctx;
(void) src;
#line 41 "spec/core_syntax.ç"

    if (!strncmp(*src, "__G2__", 6))
    {
        *src += 6;
        return strdup((char[7]) {'_', '_', 'G', '1', '_', '_', 0});     
    }
    return 0;

}
