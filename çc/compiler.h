#ifndef COMPILER_H
# define COMPILER_H
# include <libc.h>
# include <sys/mman.h>
# include <ctype.h>
# include <dlfcn.h>
# include <stdio.h>
# include <assert.h>
# include <errno.h>
# include "list.h"
# include "object.h"
# include "object_list.h"
# define USAGE_ERROR_CODE 1
# define SYSTEM_ERROR_CODE 2
# define USAGE_ERROR_EXIT(...) exit(USAGE_ERROR_CODE * (fprintf(stderr, __VA_ARGS__) && 1));
# define SYSTEM_ERROR_EXIT(K) exit(SYSTEM_ERROR_CODE * (fprintf(stderr, "%s:%i ERROR: %s failed, errno=%i\n", __FILE__, __LINE__, K, errno) && 1));
# define DEFAULT_CC "cc -Wall -Werror -Wextra -I. -I../list -I../object -DIDE_COMPAT=0 -g"

struct s_compiler_ctx;
typedef char *macro(struct s_compiler_ctx *ctx, char **str);
typedef struct s_macro_list
{
    void *handle;
    macro *item;
    struct s_macro_list *next;
} macro_list;
typedef int ctx_is(struct s_compiler_ctx);
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
    int macro_applied;
    const char *cc;
    ctx_is *is_root;
    ctx_is *is_code;
} compiler_ctx;
void free_compiler(compiler_ctx ctx);
char *format_file_name(int count);
char *format_library_name(int count);
char *format_macro_name(int count);
int cursor_incr(compiler_ctx *ctx, char **str, int i);
void *compile_macro(compiler_ctx *ctx, char *str);
int try_apply_macros(compiler_ctx *ctx, char **str);
int try_register_macros(compiler_ctx *ctx, char **str);

#ifndef IDE_COMPAT
# define IDE_COMPAT 1
#endif
#if IDE_COMPAT
# include ".macro_cleaner.h"
# include "ide_compat.h"
#endif
#endif