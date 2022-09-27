#if IDE_COMPAT
#include "ide_compat.h"
#endif
#ifndef COMPILER_H
# define COMPILER_H
# include <libc.h>
# include <sys/mman.h>
# include <ctype.h>
# include <dlfcn.h>
# include <stdio.h>
# include <assert.h>
# include <errno.h>
# include "../list/list.h"
# include "../object/object.h"
# include "../object/object_list.h"
# define ERROR(K) exit(2 * (fprintf(stderr, "%s:%i ERROR: %s failed, errno=%i\n", __FILE__, __LINE__, K, errno) && 1));
# ifndef DEFAULT_CC
#  define DEFAULT_CC "cc"
# endif

struct s_compiler_ctx;
typedef char *macro(char **str, struct s_compiler_ctx *ctx);
typedef struct s_macro_list
{
    macro *item;
    struct s_macro_list *next;
} macro_list;
typedef struct s_compiler_ctx
{
    list /*of char*/ *include_dirs;
    list /*of char*[2]*/ *defines;
    macro_list *macros;
    object_list *ol;
    char *file;
    int compile_c;
    int column;
    int line;
    int macro_count;
    int macro_depth;
    char *language;
    char *cc;
    char *out;
} compiler_ctx;
int is_code(compiler_ctx ctx);
int is_root(compiler_ctx ctx);
char *format_file_name(int count);
char *format_library_name(int count);
char *format_macro_name(int count);
int cursor_incr(compiler_ctx *ctx, char **str, int i);
void *compile_macro(compiler_ctx *ctx, char *str);
static void register_macro(compiler_ctx *ctx, char *str);
int try_apply_macros(compiler_ctx *ctx, char **str);
int try_register_macros(compiler_ctx *ctx, char **str);
#endif