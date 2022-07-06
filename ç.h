#ifndef CEDILLA_H
# define CEDILLA_H
# include <libc.h>
# define CONCAT2(X, Y)  X##Y
# define CONCAT(X, Y)   CONCAT2(X, Y)
# define STRINGIFY2(X)  #X
# define STRINGIFY(X)   STRINGIFY2(X)
# define auto           __auto_type
# define compile_time
typedef struct s_ç_ctx
{
    char                *str;
    int                 cursos_pos;
    int                 pairs_level[256];
    void                *data;
    struct s_ç_ctx      *prev_state;
}   ç_ctx;
# define macro          CONCAT(char * r_, __LINE__)(ç_ctx ctx)
# define capture        "__CEDILLA_UNTIL__",
# define until          ,"__CEDILLA_UNTIL__",
# define is             "__CEDILLA_IS__",
int match(ç_ctx ctx, ...)
{
    va_list             ap;

    va_start(ap, ctx);
    va_end(ap);
    return 0;
}
#endif