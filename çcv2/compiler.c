#include "cedilla.h"


char *format_fname(int count)
{
    char    *str;

    asprintf(&str, "objs/.tmp_macro_%i.c", count);   
    return str;
}

char *format_lname(int count)
{
    char    *str;

    asprintf(&str, "objs/.tmp_macro_%i.so", count);   
    return str;
}

char *format_mname(int count)
{
    char    *str;

    asprintf(&str, "cedilla_macro_%i", count);
    return str;
}

void *compile_macro(char *str)
{
    int     fd;
    char    *cmd;

    fd = open(format_fname(macro_count), O_WRONLY | O_CREAT | O_TRUNC, 0777);
    dprintf(fd, 
        "#include \"cedilla.h\"\n"
        "\n"
        "char *%s(char **str, parser_ctx *ctx) { %s }\n",
        format_mname(macro_count),
        str
    );
    close(fd);
    asprintf(&cmd, "cc -I. -shared -fPIC -o %s %s\n", format_lname(macro_count), format_fname(macro_count));
    system(cmd);

    void *handle = dlopen (format_lname(macro_count), RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "Unable to load macro '%s'. Reason=%s\n", format_lname(macro_count), dlerror());
        exit(1);
    }
    dlerror();    /* Clear any existing error */
    void *r = dlsym(handle, format_mname(macro_count));
    char *error;
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "Unable to load macro func '%s' within '%s' Reason=%s\n", format_mname(macro_count), format_lname(macro_count), error);
        exit(1);
    }
    return r;
}

void register_macro(macro_list **macros, char *str)
{
    macro_list *it;

    if (!*macros)
    {
        *macros = malloc(sizeof(macro_list));
        (*macros)->item = compile_macro(str);
        (*macros)->next = 0;
        macro_count += 1;
        return ;
    }
    it = *macros;
    while (1)
    {
        if (!it->next)
        {
            it->next = malloc(sizeof(macro_list));
            it->next->item = compile_macro(str);
            it->next->next = 0;
            macro_count += 1;
            return ;
        }
        it = it->next;
    }
}

int    try_register_macros(macro_list **macros, char **str, parser_ctx *ctx);


int     try_apply_macros(macro_list **macros, char **str, parser_ctx *ctx)
{
    macro_list  *it;
    char        *prefix;
    char        *new_str;

    it = *macros;
    while (it)
    {
        if ((prefix = it->item(str, ctx)))
        {
            asprintf(str, "%s%s", prefix, *str);
            // new_str ///
            ctx->levels.depth += 1;
            try_register_macros(macros, str, ctx); 
            try_apply_macros(macros, str, ctx);
            return (1);
        }
        it = it->next;
    }
    ctx->levels.depth = 0;
    return (0);
}

void     cursor_incr(char **str, parser_ctx *ctx, int i)
{
    while (i && **str)
    {
        if (!ctx->levels.depth)
        {
            if (*((*str) + i) == '\n')
            {
                ctx->levels.lines += 1;
                ctx->levels.collumns = 1;
            }
            else
            {
                ctx->levels.collumns += 1;
            }
        }
        *str += 1;
        i -= 1;
    }
}

int     ctx_is_code(parser_ctx ctx)
{
    return (!ctx.is.comment && !ctx.is.comments && !ctx.is.chr && !ctx.is.str);
} 

int     ctx_is_root(parser_ctx ctx)
{
    return (ctx_is_code(ctx) && !ctx.levels.parentheses && !ctx.levels.brackets && !ctx.levels.braces);
}

int    try_register_macros(macro_list **macros, char **str, parser_ctx *ctx)
{
    if (!ctx_is_root(*ctx))
        return (0);
     if (strncmp(*str , "macro", 5))
        return (0);
    if (!isspace((*str)[5]))
        return (0);
    cursor_incr(str, ctx, 5);
    while (isspace(**str))
    {
        cursor_incr(str, ctx, 1);
    }
    if (**str != '{')
    {
        printf("ERROR: '{' expected at line %i and col %i\n", ctx->levels.lines, ctx->levels.collumns);
        exit(1);
    } 
    ctx->levels.braces = 1;
    cursor_incr(str, ctx, 1);
    char *new_str = 0;
    while (ctx->levels.braces && *str)
    {
        if (!try_apply_macros(macros, str, ctx))
        {
            asprintf(&new_str, "%s%c", new_str ? new_str : "", **str);
            cursor_incr(str, ctx, 1);       
        }
        if (**str == '{' && ctx_is_code(*ctx))
        {
            ctx->levels.braces += 1;
        }
        if (**str == '}' && ctx_is_code(*ctx))
        {
            ctx->levels.braces -= 1;
            if (!ctx->levels.braces)
            {
                cursor_incr(str, ctx, 1);
            }
        }
    }
    if (ctx->levels.braces)
    {
        printf("ERROR: '}' expected at line %i and col %i\n", ctx->levels.lines, ctx->levels.collumns);
        exit(1);
    }
    register_macro(macros, new_str); 
    return (1);
}

int main(int ac, char **av)
{
    if (ac != 2)
    {
        printf ("Usage: %s [file.c]\n", av[0]);
        return (0);
    }

    int fd = open (av[1], O_RDONLY);
    int len = lseek(fd, 0, SEEK_END);
    char *str = mmap(0, len, PROT_READ, MAP_PRIVATE, fd, 0);

    char *new_str = 0;

    macro_list *macros = 0;
    parser_ctx ctx = (parser_ctx) {
        .is = {.comment = 0, .comments = 0, .str = 0, .chr = 0},
        .levels = {.braces = 0, .parentheses = 0, .depth = 0, .collumns = 0, .lines = 0}
    };

    while (*str)
    {
        
        try_register_macros(&macros, &str, &ctx); 
        if (!try_apply_macros(&macros, &str, &ctx))
        {
            asprintf(&new_str, "%s%c", new_str ? new_str : "", *str);
            cursor_incr(&str, &ctx, 1);       
        }
        
        // for each macro
        //if macro match ...
        //    replace data by appending result  
        
        //if macro ...
        //    register macro 
    }

    printf("%s", new_str);
}
