#ifndef MATCH_H
# define MATCH_H
# include <libc.h>
# include "./object.h"
# define capture        "__CEDILLA_UNTIL__"
# define until          "__CEDILLA_UNTIL__"
# define is             "__CEDILLA_IS__"
typedef struct s_ç_ctx
{
    char                    *str;
    int                     pos;
    object                  *identifiers;
}   ç_ctx;
int match(ç_ctx *, ...);
int vmatch(ç_ctx *, va_list);
#endif