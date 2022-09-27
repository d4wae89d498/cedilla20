#include "compiler.h"

void    free_compiler(compiler_ctx ctx)
{
    list_free(ctx.defines, free);
    list_free(ctx.include_dirs, free); 
    macro_list *it = ctx.macros;
    macro_list *swp;
    while (it)
    {
        swp = it->next;
        dlclose(it->handle);
        free(it);
        it = it->next;
    }
    olist_free(ctx.ol);
}

char *format_file_name(int count)
{
    char    *str;

    asprintf(&str, "objs/.tmp_macro_%i.c", count);   
    return str;
}

char *format_library_name(int count)
{
    char    *str;

    asprintf(&str, "objs/.tmp_macro_%i.so", count);   
    return str;
}

char *format_macro_name(int count)
{
    char    *str;

    asprintf(&str, "cedilla_macro_%i", count);
    return str;
}

int     cursor_incr(compiler_ctx *ctx, char **str, int i)
{
    int     y;

    y = 0;
    while (i && **str)
    {
        if (!ctx->macro_depth)
        {
            if (*((*str) + i) == '\n')
            {
                ctx->line += 1;
                ctx->column = 1;
            }
            else
            {
                ctx->column += 1;
            }
        }
        *str += 1;
        i -= 1;
        y += 1;
    }
    return (y);
}

void *compile_macro(compiler_ctx *ctx, char *str)
{
    int     fd;
    char    *cmd;
    char    *file_name;
    char    *library_name;
    char    *macro_name;
    int     k;

    fprintf(stderr, "compiling macro from file: %s ...\n", ctx->file);
    file_name = format_file_name(ctx->macro_count);
    if (!file_name)
        return (0);
    library_name = format_library_name(ctx->macro_count);
    if (!library_name)
    {
        free(file_name);
        return (0);
    }
    macro_name = format_macro_name(ctx->macro_count);
    if (!macro_name)
    {
        free(file_name);
        free(library_name);
        return (0);
    }
    fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (fd < 0)
    {
        fprintf(stderr, "open\n");
        return (0);
    }
    if (dprintf(fd, 
        "#include \"compiler.h\"\n"
        "#define main main4242\n"
        "#undef IDE_COMPAT\n"
        "#define IDE_COMPAT 0\n"
        "char *%s(compiler_ctx *ctx, char **src) { %s }\n",
        macro_name,
        str
    ) < 0)
    {
        fprintf(stderr, "dprintf\n");
        return (0);
    }
    close(fd);
    asprintf(&cmd, "cc -DIDE_COMPAT=0 -I. -shared -fPIC -o %s %s\n", library_name, file_name);
    if (!cmd)
    {
        fprintf(stderr, "malloc\n");
        return (0);
    }
    k = system(cmd);
    if (k < 0)
    {
        fprintf(stderr, "system\n");
        return (0);
    }
    else if (k)
    {
        fprintf(stderr, "Macro compilation error=%i\n", k);
        return (0);
    }
    free(cmd);
    void *handle = dlopen (format_library_name(ctx->macro_count), RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "Unable to load macro '%s'. Reason=%s\n", format_library_name(ctx->macro_count), dlerror());
        return (0);
    }
    dlerror();
    return (handle);
}

static int register_macro(compiler_ctx *ctx, char *str)
{
    macro_list *it;

    void *handle = compile_macro(ctx, str); 
    if (!handle)
        return (-SYSTEM_ERROR_CODE);
    void *item = dlsym(handle, format_macro_name(ctx->macro_count));
    char *error;
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "Unable to load macro func '%s' within '%s' Reason=%s\n", format_macro_name(ctx->macro_count), format_library_name(ctx->macro_count), error);
        dlclose(handle);
        return (-SYSTEM_ERROR_CODE);
    }
    if (!ctx->macros)
    {
        ctx->macros = malloc(sizeof(macro_list));
        if (!ctx->macros)
        {
            dlclose(handle);
            fprintf(stderr, "malloc\n");
            return (-SYSTEM_ERROR_CODE);
        }
        (ctx->macros)->item = item;
        (ctx->macros)->handle = handle;
        (ctx->macros)->next = 0;
        ctx->macro_count += 1;
        return (0);
    }
    it = ctx->macros;
    while (1)
    {
        if (!it->next)
        {
            it->next = malloc(sizeof(macro_list));
            if (!it->next)
            {
                dlclose(handle);
                fprintf(stderr, "malloc\n");
                return (-SYSTEM_ERROR_CODE);
            }
            it->next->item = item;
            it->next->handle = handle;
            it->next->next = 0;
            ctx->macro_count += 1;
            return (0);
        }
        it = it->next;
    }
    return (-SYSTEM_ERROR_CODE);
}

int     try_apply_macros(compiler_ctx *ctx, char **str)
{
    macro_list  *it;
    char        *prefix;
    char        *swp;

    it = ctx->macros;
    while (it)
    {
        if ((prefix = it->item(ctx, str)))
        {
            swp = *str;
            asprintf(str, "%s%s", prefix, *str);
            if (!str)
            {
                fprintf(stderr, "malloc\n");
                return(-SYSTEM_ERROR_CODE);
            }
            free(swp);
            free(prefix);
            ctx->macro_depth += 1;
            int x = try_register_macros(ctx, str); 
            if (x < 0)
                return (x);
            int y = try_apply_macros(ctx, str);
            if (y < 0)
                return (y);
            return (strlen(prefix) + x + y);
        }
        it = it->next;
    }
    ctx->macro_depth = 0;
    return (0);
}

int    try_register_macros(compiler_ctx *ctx, char **str)
{
    int r;

    r = 0;
    if (!ctx->is_root(*ctx))
        return (0);
     if (strncmp(*str , "macro", 5))
        return (0);
    if (!isspace((*str)[5]))
        return (0);
    r += cursor_incr(ctx, str, 5);
    while (isspace(**str))
    {
        r += cursor_incr(ctx, str, 1);
    }
    if (**str != '{') // try apply macro here n4
    {
        fprintf(stderr, "ERROR: '{' expected at line %i and col %i\n", ctx->line, ctx->column);
        return (-USAGE_ERROR_CODE);
    } 
    int braces_level = 1;
    r += cursor_incr(ctx, str, 1);
    char *new_str = 0;
    while (braces_level && *str)
    {
        int x = try_apply_macros(ctx, str);
        if (x < 0)
            return (x);
        if (!x)
        {
            char *swp = new_str;
            asprintf(&new_str, "%s%c", new_str ? new_str : "", **str);
            if (!new_str)
            {
                fprintf(stderr, "malloc\n");
                return (-SYSTEM_ERROR_CODE);
            }
            free(swp);
            r += cursor_incr(ctx, str, 1);       
        }
        if (**str == '{' && ctx->is_code(*ctx))
        {
            braces_level += 1;
        }
        if (**str == '}' && ctx->is_code(*ctx))
        {
            braces_level -= 1;
            if (!braces_level)
            {
                r += cursor_incr(ctx, str, 1);
            }
        }
    }
    if (braces_level)
    {
        fprintf(stderr, "ERROR: '{' expected at line %i and col %i\n", ctx->line, ctx->column);
        return (-USAGE_ERROR_CODE);
    }
    int k = register_macro(ctx, new_str);
    if (k)
        return (k);
    return (r);
}