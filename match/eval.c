#include "match.h"

static void str_suffix(char **str, char *suffix)
{
    char    *new_str;

    asprintf(&new_str, "%s%s", *str, suffix);
    free(*str);
    *str = new_str;
}

static void str_prefix(char **str, char *prefix)
{
    char    *new_str;

    asprintf(&new_str, "%s%s", prefix, *str);
    free(*str);
    *str = new_str;
}

int eval(match_ctx *ctx, va_list ap)
{
    int i;
    char *original_str;
    char *r;
    object_list *it;
    char *ostr;
    int matched;
    object_list *bkp;


    original_str = ctx->str;
    ctx->str = ostr = strdup(va_arg(ap, char *));
    __parse:
    while (ctx->str[0])
    {
        printf("match_char: %c\n", ctx->str[0]);
        matched = 0;
        it = get(ctx->o, macro_list, object_list*);
        while (it)
        {
            bkp = olist_clone(ctx->o);
            printf("trying macro %p\n", (void*)it->data->value);
            if ((r = ((macro_function)it->data->value)(ctx)))
            {
                matched = 1;
                if (r != ctx->str)
                    str_prefix(&(ctx->str), r);
                goto __parse;
            }
            olist_free(ctx->o);
            ctx->o = bkp;
            it = it->next;
        }
        if (!matched)
        {
            str_suffix(&(ctx->output), (char[2]){ctx->str[0], 0});
            ctx->str += 1;
        }
    }
    i = ostr - ctx->str;
    free(ostr);
    ctx->str = original_str;
    return i;
}