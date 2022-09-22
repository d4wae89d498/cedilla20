#ifndef IDE_COMPAT
# define IDE_COMPAT 1
#endif
#ifndef TEST
# define TEST 1
#endif
#if IDE_COMPAT
# include ".macro_cleaner.h"
#endif
#ifndef CEDILLA_H
# define CEDILLA_H
# include "libc.h"
# include "sys/mman.h"
# include "ctype.h"
# include "dlfcn.h"
# include "stdio.h"
# include "assert.h"

typedef struct s_compile_time_list
{
    char                   *item;
    struct s_macro_list    *next;   
} compile_time_list;
typedef struct s_parser_ctx
{
    struct 
    {
        int comment:        1;
        int comments:       1;
        int chr:            1;
        int str:            1;
    } is;
    struct
    {
        int parentheses:    16;
        int brackets:       16;
        int braces:         16;
        int depth:          16;
        int columns:       16;
        int lines:          16;
    } levels;
    char *file;

} parser_ctx;
struct s_macro_list;
typedef char*   macro (struct s_macro_list **macros, char **str, parser_ctx *ctx);
typedef struct s_macro_list
{
    macro                  *item;
    struct s_macro_list    *next;   
} macro_list;
int macro_count = 0;
# if IDE_COMPAT
char        **src;
parser_ctx  ctx;
# endif
int     try_register_macros(macro_list **macros, char **str, parser_ctx *ctx);
int     try_apply_macros(macro_list **macros, char **str, parser_ctx *ctx);

int     ctx_is_code(parser_ctx ctx)
{
    return (!ctx.is.comment && !ctx.is.comments && !ctx.is.chr && !ctx.is.str);
} 

int     ctx_is_root(parser_ctx ctx)
{
    return (ctx_is_code(ctx) && !ctx.levels.parentheses && !ctx.levels.brackets && !ctx.levels.braces);
}

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

int     cursor_incr(char **str, parser_ctx *ctx, int i)
{
    int     y;

    y = 0;
    while (i && **str)
    {
        if (!ctx->levels.depth)
        {
            if (*((*str) + i) == '\n')
            {
                ctx->levels.lines += 1;
                ctx->levels.columns = 1;
            }
            else
            {
                ctx->levels.columns += 1;
            }
        }
        *str += 1;
        i -= 1;
        y += 1;
    }
    return (y);
}

void *compile_macro(char *str, parser_ctx *ctx)
{
    int     fd;
    char    *cmd;

    fprintf(stderr, "compiling macro from file: %s ...\n", ctx->file);

//    printf("");

    fd = open(format_fname(macro_count), O_WRONLY | O_CREAT | O_TRUNC, 0777);
    dprintf(fd, 
        "#include \"cedilla.h\"\n"
        "#define main main4242\n"
        "#undef IDE_COMPAT\n"
        "#define IDE_COMPAT 0\n"
        "char *%s(macro_list **macros, char **src, parser_ctx *ctx) { %s }\n",
        format_mname(macro_count),
        str
    );
    close(fd);
    asprintf(&cmd, "cc -DIDE_COMPAT=0 -I. -shared -fPIC -o %s %s\n", format_lname(macro_count), format_fname(macro_count));
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

static void register_macro(macro_list **macros, char *str, parser_ctx *ctx)
{
    macro_list *it;

    if (!*macros)
    {
        *macros = malloc(sizeof(macro_list));
        (*macros)->item = compile_macro(str, ctx);
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
            it->next->item = compile_macro(str, ctx);
            it->next->next = 0;
            macro_count += 1;
            return ;
        }
        it = it->next;
    }
}

int     try_apply_macros(macro_list **macros, char **str, parser_ctx *ctx)
{
    macro_list  *it;
    char        *prefix;
    char        *new_str;

    it = *macros;
    while (it)
    {
        if ((prefix = it->item(macros, str, ctx)))
        {
            asprintf(str, "%s%s", prefix, *str);
            // new_str ///
            ctx->levels.depth += 1;
            int x = try_register_macros(macros, str, ctx); 
            int y = try_apply_macros(macros, str, ctx);
            return (strlen(prefix) + x + y);
        }
        it = it->next;
    }
    ctx->levels.depth = 0;
    return (0);
}

int    try_register_macros(macro_list **macros, char **str, parser_ctx *ctx)
{
    int r;

    r = 0;
    if (!ctx_is_root(*ctx))
        return (0);
     if (strncmp(*str , "macro", 5))
        return (0);
    if (!isspace((*str)[5]))
        return (0);
    r += cursor_incr(str, ctx, 5);
    while (isspace(**str))
    {
        r += cursor_incr(str, ctx, 1);
    }
    if (**str != '{')
    {
        printf("ERROR: '{' expected at line %i and col %i\n", ctx->levels.lines, ctx->levels.columns);
        exit(1);
    } 
    ctx->levels.braces = 1;
    r += cursor_incr(str, ctx, 1);
    char *new_str = 0;
    while (ctx->levels.braces && *str)
    {
        if (!try_apply_macros(macros, str, ctx))
        {
            asprintf(&new_str, "%s%c", new_str ? new_str : "", **str);
            r += cursor_incr(str, ctx, 1);       
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
                r += cursor_incr(str, ctx, 1);
            }
        }
    }
    if (ctx->levels.braces)
    {
        printf("ERROR: '{' expected at line %i and col %i\n", ctx->levels.lines, ctx->levels.columns);
        exit(1);
    }
    register_macro(macros, new_str, ctx); 
    return (r);
}
# include "match.h"

# define CEDILLA_CONCAT2(X, Y)  X##Y
# define CEDILLA_CONCAT(X, Y)   CEDILLA_CONCAT2(X, Y)
# define CEDILLA_STR2(X)         #X
# define CEDILLA_STR(X)        CEDILLA_STR2(X)
# define CEDILLA_CONCAT2(X, Y)  X##Y
# define CEDILLA_CONCAT(X, Y)   CEDILLA_CONCAT2(X, Y)
# define debugg(...) #__VA_ARGS__
# define each_test(x) , (x + 1)
# define dump_macro(...) printf("[%s:%i dump_macro] %s\n", __FILE__, __LINE__, apply(str, __VA_ARGS__));
# define cdump(...) message(apply(str, __VA_ARGS__))
# define macro CEDILLA_CONCAT(char * cedilla_macro_, __LINE__)(macro_list **macros, char **src, parser_ctx *ctx)

#endif