#include "./../include/match.h"

int match_capture(ç_ctx *ctx, va_list ap)
{
    printf("captre found!!!");
    return 1;
}

/*
 * todo:: store current ctx copy in ctx->prev_state and restore it on failure at each return 0
 */
int vmatch(ç_ctx *ctx, va_list ap)
{
    char        *arg_str;
    unsigned    i;
    unsigned    arg_str_len;
 
    arg_str = (void*)1;
    while (arg_str)
    {
        arg_str = va_arg(ap, char *);
        if (!arg_str)
            break ;
        arg_str_len = strlen(arg_str);
        if (!strncmp(ctx->str + ctx->cursos_pos, arg_str, arg_str_len))
        {
            ctx->cursos_pos += arg_str_len;
            continue ;
        } 
        i = 0;
        while (m_instructions[i].name && m_instructions[i].function)
        {
            if (!strcmp(arg_str, m_instructions[i].name))
            {
                if (m_instructions[i].function(ctx, ap))
                    break ;
                else
                    return 0;
            } 
            i += 1;
        }
        if (!(m_instructions[i].name) | !(m_instructions[i].function))
            return 0;
    }
    return 1;
}

int match(ç_ctx *ctx, ...)
{
    va_list ap;
    int r;

    va_start(ap, ctx);
    r = vmatch(ctx, ap);
    va_end(ap);
    return r;
}

#if CEDILLA_TEST == 1
# include "assert.h"
int main()
{
    ç_ctx   ctx;
    int     r;

    printf("testing match...\n");  
    ctx.str = "HELLO WORLD";
    r = match(&ctx, "HELLO", " ", "WORLD", 0);
    assert(r == 1);
    r = match(&ctx, "HELLO", 0);
    assert(r == 1); // todo: fix me
}
#endif