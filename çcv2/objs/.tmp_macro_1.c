#include "cedilla.h"
#define main main4242
#undef IDE_COMPAT
#define IDE_COMPAT 0
char *cedilla_macro_1(macro_list **macros, char **src, parser_ctx *ctx) { 
    char        *new_src = *src;
    parser_ctx  new_ctx = *ctx;
    char        *file_path = "";

    if (ctx_is_code(*ctx) && !ctx->levels.brackets && !ctx->levels.parentheses)
    {
        if ((!ctx->levels.columns || *(new_src - 1) == '\n') && ctx_is_code(*ctx) && !ctx->levels.parentheses && !ctx->levels.brackets)
        {
            if (!(*new_src == '#'))
                return 0;
            cursor_incr(&new_src, &new_ctx, 1);
            fprintf(stderr, "CPP %s\t%i:%i\n", ctx->file, ctx->levels.lines, ctx->levels.columns);
            while (isspace(*new_src) && *new_src != '\n')
                cursor_incr(&new_src, &new_ctx, 1);
            if (*new_src == '\n')
                return (0);
            if (!strncmp(new_src, "include", 7))
            {
                cursor_incr(&new_src, &new_ctx, 7);
                fprintf(stderr, "INCLUDE!! [%.10s]\n", new_src);
                while (isspace(*new_src) && *new_src != '\n')
                    cursor_incr(&new_src, &new_ctx, 1);
                if (*new_src == '\n')
                {
                    fprintf(stderr, "%s: error: unexpected '\\n' at line %i and col %i\n", ctx->file, ctx->levels.lines, ctx->levels.columns);
                }
                else if (*new_src == '\"')
                {
                    cursor_incr(&new_src, &new_ctx, 1);
                    while (*new_src && *new_src != '\"' && *new_src != '\n')
                    {
                        asprintf(&file_path, "%s%c", file_path, *new_src);
                        cursor_incr(&new_src, &new_ctx, 1);
                    }
                    if (!*new_src || *new_src == '\n')
                    {
                        fprintf(stderr, "%s: error: unexpected '\\n' at line %i and col %i\n", ctx->file, ctx->levels.lines, ctx->levels.columns);
                    }
                    else 
                    {
                        fprintf(stderr, "INCLUDE FILE: %s\n", file_path);
                    }
                }
                else if (*new_src == '<')
                {
                    cursor_incr(&new_src, &new_ctx, 1);
                    while (*new_src && *new_src != '>' && *new_src != '\n')
                    {
                        asprintf(&file_path, "%s%c", file_path, *new_src);
                        cursor_incr(&new_src, &new_ctx, 1);
                    }
                    if (!*new_src || *new_src == '\n')
                    {
                        fprintf(stderr, "%s: error: unexpected '\\n' at line %i and col %i\n", ctx->file, ctx->levels.lines, ctx->levels.columns);
                    }
                    else 
                    {
                        fprintf(stderr, "INCLUDE FILE (W/ INCLUDE_PATH): %s\n", file_path);
                    }
                }
                else 
                {
                    fprintf(stderr, "%s: error: unexpected '%c' at line %i and col %i\n", ctx->file, *new_src, ctx->levels.lines, ctx->levels.columns);
                }
            }

        }
    }
    return (0);
 }
