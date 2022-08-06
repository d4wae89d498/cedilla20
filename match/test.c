#include "match.h"

char *parentheses_macro(match_ctx *ctx)
{
    object_list **o = &(ctx->o);

    printf("pmacro called...\n");

    if (!exists(*o, plvl))
        rset(o, new (int, plvl, 0));
    if (match(ctx, str_is, "("))
        rset(o, new (int, plvl, get(*o, plvl, int) + 1));
    else if (match(ctx, str_is, ")"))
        rset(o, new (int, plvl, get(*o, plvl, int) - 1));
    else
        return 0;
    printf("parenthese found!\n");
    ctx->str += 1;
    return ctx->str;
}

int any(match_ctx *ctx, va_list ap)
{
    (void) ctx;
    (void) ap;
    return 1;
}

int dump_plvl(match_ctx *ctx, va_list ap)
{
    (void)ap;

    printf("plvl=%i\n", get(ctx->o, plvl, int));
    return 1;
}

int main()
{
    match_ctx ctx =
        {
            .o = 0,
            .str = "  1 2  (4 + (9 * 8))",
            .output = strdup("")};
    set(&(ctx.o), macro_list, new (macro_function, m1, parentheses_macro));
    char *buffer = 0;
    match(&ctx,
          print_int, 10,
          skip, is_space, limit, 5, until, is_digit,
          skip, is_digit,
          print_str,
          skip, is_space,
          skip, is_digit,
          skip, is_space,
          parse, "(",
          skip, any, until, parse, "(",
          dump_plvl,
          capture, &buffer, until, str_is, ")"
    );

    printf("%s\n", buffer);
}
