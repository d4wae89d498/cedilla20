#include "compiler.h"
#define main main4242
#undef IDE_COMPAT
#define IDE_COMPAT 0
char *cedilla_macro_4(macro_list **macros, char **src, compiler_ctx *ctx) { 
    if (!is_code(*ctx) && !strncmp(*src, "comment_compile_time_assert_str_eq", 34))
    {
        *src += 34;
        while (isspace(**src))
            *src += 1;
        try_apply_macros(macros, src, ctx);
        int a = 0;
        while (isdigit(**src))
        {
            a *= 10;
            a += **src - '0';
            *src += 1;
        }
        while (isspace(**src))
            *src += 1;
        int b = 0;
        while (isdigit(**src))
        {
            b *= 10;
            b += **src - '0';
            *src += 1;
        }
        assert(a == b);
    }
    return (0);
 }
