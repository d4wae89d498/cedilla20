#include "compiler.h"

const char *help = "Type çc --help for help.\n";
const char *itermediate_file = "./tmp_cedilla_intermediate_output.c";

static compiler_ctx parse_args(int ac, char **av)
{
    compiler_ctx o;
    o.compile_c = true;
    o.cc = DEFAULT_CC;
    int i = 1;
    while (i < ac)
    {
        if (av[i][0] != '-')
            exit(fprintf(stderr, "Error, unknow çc flag : %s\n%s", av[i], help) && 1);
        if (!strcmp(av[i], "-CC"))
        {
            i += 1;
            if (i >= ac)
                exit (printf(stderr, "Error, expected <value> after -CC\n%s", help) && 1);
            o.cc = av[i];
        }
        else if (av[i][1] == 'D')
        {
            char **item = malloc(2 * sizeof(char*));
            if (!item)
            {
                list_free(o.defines, free);
                list_free(o.include_dirs, free);
                ERROR("malloc");
            }
            int k = 0;
            if (!av[i][2] && ++i >= ac)
                exit (printf(stderr, "Error, expected <macro>=<value> after -D\n%s", help) && 1);   
            else 
                k += 2;
            (*item)[0] = av[i];
            while(av[i][k])
            {
                if (av[i][k] == '=')
                {
                    av[i][k] = 0;
                    k += 1;
                    break ;
                }   
                k += 1;
            }
            (*item)[1] = (av[i][k]) ? &(av[i][k]) : "1";
            if (!list_add(o.defines, item))
            {
                free(item);
                list_free(o.defines, free);
                list_free(o.include_dirs, free);
                ERROR("list_add::malloc");  
            }
        }
        else if (av[i][1] == 'E')
            o.compile_c = false;
        else if (av[i][1] == 'I')
        {
            char *include_dir;
            if (!av[i][2])
            {
                i += 1;
                if (i >= ac)
                    exit (printf(stderr, "Error, expected <dir> after -I\n%s", help) && 1);
                include_dir = av[i];
            }
            else 
                include_dir = &(av[i][2]);
            if (!list_add(o.include_dirs, include_dir))
            {
                list_free(o.defines, free);
                list_free(o.include_dirs, free);
                ERROR("list_add::malloc");  
            }
        }
        else if (!strcmp(av[i], "--help"))
            exit(printf("OVERVIEW: çc extensible GPL implementation that targets C99.\n\nUSAGE: çc [options] <inputs>\n\nOPTIONS:\n"
                "-CC <value>            Define the C compiler and its flags\n"
                "-D <macro>=<value>     Define <macro> to <value> (or 1 if <value> omitted)\n"  
                "-E                     Only run the preprocessor\n"
                "-I <dir>               Add directory to include search path\n" 
                "-o <value>             "
                "--help                 Display available options\n"
            ) && 0);
        i += 1;
    }
 
    return (o);
}

/*
 * Exit codes : 
 *  0 - Normal exit
 *  1 - Usage error
 *  2 - System error
 */
int main(int ac, char **av)
{
    compiler_ctx    ctx = parse_args(ac, av);
    int             fd = open (av[1], O_RDONLY);
    if (fd < 0)
        ERROR("open");
    int             len = lseek(fd, 0, SEEK_END);
    char            *str = mmap(0, len, PROT_READ, MAP_PRIVATE, fd, 0);
    if (str == MAP_FAILED)
    {
        close (fd);
        ERROR("mmap");
    }
    char            *new_str = 0;
    while (*str)
    {
        try_register_macros(&ctx, &str); 
        if (!try_apply_macros(&ctx, &str))
        {
            asprintf(&new_str, "%s%c", new_str ? new_str : "", *str);
            cursor_incr(&str, &ctx, 1);       
        }
    }
    if (!ctx.compile_c)
        printf("%s", new_str);
    else 
    {
        char *cmd;
        asprintf("echo <<<\"EOF\"\n"
                 "%s\n"
                 "EOF >> %s && %s %s; rm -f %s;", new_str, itermediate_file, ctx.cc, itermediate_file, itermediate_file);
        free(cmd);
    }
    free(new_str);
    free(str);
    close(fd);
}