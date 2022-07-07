#ifndef MATCH_H
# define MATCH_H
# include <libc.h>
# define capture        "__CEDILLA_UNTIL__"
# define until          "__CEDILLA_UNTIL__"
# define is             "__CEDILLA_IS__"

typedef struct s_ç_ctx
{
    char                    *str;
    int                     cursos_pos;
    int                     pairs_level[256];
    void                    *data;
    struct s_ç_ctx          *prev_state;
}   ç_ctx;
typedef struct 
{
    char                    *name;
    int                     (*function)(ç_ctx*, va_list);
}   match_instruction;
extern match_instruction    m_instructions[1024];
int match(ç_ctx *, ...);
int vmatch(ç_ctx *, va_list);
#endif