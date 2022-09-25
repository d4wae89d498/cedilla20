#include "../object/object_list.h"
#if IDE_COMPAT
#include "ide_compat.h"
#endif
#ifndef CEDILLA_H
#define CEDILLA_H
#include "libc.h"
#include "sys/mman.h"
#include "ctype.h"
#include "dlfcn.h"
#include "stdio.h"
#include "assert.h"

struct s_parser_ctx;
typedef char *macro(char **str, struct s_parser_ctx *ctx);
typedef struct s_macro_list
{
    macro *item;
    struct s_macro_list *next;
} macro_list;
typedef struct s_parser_ctx
{
    macro_list *macros;
    object_list *ol;
    char *file;
    int column;
    int line;
    int macro_count;
    char *language;
} parser_ctx;
int try_register_macros(macro_list **macros, char **str, parser_ctx *ctx);
int try_apply_macros(macro_list **macros, char **str, parser_ctx *ctx);
int ctx_is_code(parser_ctx ctx);
int ctx_is_root(parser_ctx ctx);
char *format_fname(int count);
char *format_lname(int count);
char *format_mname(int count);
int cursor_incr(char **str, parser_ctx *ctx, int i);
void *compile_macro(char *str, parser_ctx *ctx);
static void register_macro(macro_list **macros, char *str, parser_ctx *ctx);
int try_apply_macros(macro_list **macros, char **str, parser_ctx *ctx);
int try_register_macros(macro_list **macros, char **str, parser_ctx *ctx);
#endif