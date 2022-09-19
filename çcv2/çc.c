#include "cedilla.h"


int main(int ac, char **av)
{
    if (ac != 2)
    {
        printf ("Usage: %s [file.c]\n", av[0]);
        return (0);
    }
    int         fd = open (av[1], O_RDONLY);
    int         len = lseek(fd, 0, SEEK_END);
    char        *str = mmap(0, len, PROT_READ, MAP_PRIVATE, fd, 0);
    char        *new_str = 0;
    macro_list  *macros = 0;
    parser_ctx  ctx = (parser_ctx) {
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
    }
    printf("%s", new_str);
}