#include "match.h"

int str_suffix(char **str, char *suffix)
{
    char    *new_str;

    if (!*str)
        *str = strdup("");
    asprintf(&new_str, "%s%s", *str, suffix);
    free(*str);
    *str = new_str;
    return (1);
}

int str_prefix(char **str, char *prefix)
{
    char    *new_str;

    if (!*str)
        *str = strdup("");
    asprintf(&new_str, "%s%s", prefix, *str);
    free(*str);
    *str = new_str;
    return (1);
}

int eval(match_ctx *ctx, va_list ap)
{
    int i;
    char *r;
    object_list *it;
    char *ostr;
    int matched;
 
    char *original_str;

    object_list *o;
    char    *output;
    char    *str;   

    original_str = ctx->str;
    ctx->str = ostr = strdup(va_arg(ap, char *));
    __parse:
    while (ctx->str[0])
    {
        printf("match_char: %c\n", ctx->str[0]);
        matched = 0;
        it = vget(ctx->o, macro_list, object_list*);
        while (it)
        {
            o = olist_clone(ctx->o);
            str = strdup(ctx->str);
            output = strdup(ctx->output);
            printf("trying macro %p\n", (void*)it->data->value);
            if ((r = ((macro_function)it->data->value)(ctx)))
            {
                matched = 1;
                if (r != ctx->str)
                    str_prefix(&(ctx->str), r);
                goto __parse;
            }
            olist_free(ctx->o);
            ctx->o = o;
            free(ctx->str);
            ctx->str = str;
            free(ctx->output);
            ctx->output = output;
            it = it->next;
        }
        if (!matched)
        {
            str_suffix(&(ctx->output), (char[2]){ctx->str[0], 0});
            ctx->str += 1;
        }
    }
    i = strlen(ostr);//ostr - ctx->str;
   // if (ctx->str != ostr)
    free(ostr);
    ctx->str = original_str;
    return i;
}