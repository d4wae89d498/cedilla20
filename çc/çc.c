#include "compiler.h"

const char *help = "Type çc --help for help.\n";
const char *itermediate_file = "./tmp_cedilla_intermediate_output.c";
const char *default_cc = "cc";

static int is_code(compiler_ctx ctx)
{
    (void)ctx;
    return (1);
}

static int is_root(compiler_ctx ctx)
{
    (void)ctx;
    return (1);
}

static compiler_ctx parse_args(int ac, char **av)
{
    compiler_ctx o = {
        .file = 0,
        .defines = 0,
        .include_dirs = 0,
        .macros = 0,
        .line = 0,
        .column = 0,
        .ol = 0,
        .macro_count = 0,
        .macro_depth = 0,
        .compile_c = true,
        .cc = default_cc,
        .is_code = is_code,
        .is_root = is_root};
    int i = 1;
    while (i < ac)
    {
        if (av[i][0] != '-')
        {
            if (o.file)
            {
                free_compiler(o);
                USAGE_ERROR_EXIT("Error, only one file is supported by the çc command.\n%s", help);
            }
            o.file = av[i];
        }
        else if (!strcmp(av[i], "-CC"))
        {
            i += 1;
            if (i >= ac)
            {
                free_compiler(o);
                USAGE_ERROR_EXIT("Error, expected <value> after -CC\n%s", help);
            }
            o.cc = av[i];
        }
        else if (av[i][1] == 'D')
        {
            char **item = malloc(2 * sizeof(char *));
            if (!item)
            {
                free_compiler(o);
                SYSTEM_ERROR_EXIT("malloc");
            }
            int k = 0;
            if (!av[i][2] && ++i >= ac)
            {
                free_compiler(o);
                USAGE_ERROR_EXIT("Error, expected <macro>=<value> after -D\n%s", help);
            }
            else
                k += 2;
            (item)[0] = av[i];
            while (av[i][k])
            {
                if (av[i][k] == '=')
                {
                    av[i][k] = 0;
                    k += 1;
                    break;
                }
                k += 1;
            }
            (item)[1] = (av[i][k]) ? &(av[i][k]) : "1";
            if (!list_add(&(o.defines), item))
            {
                free(item);
                free_compiler(o);
                SYSTEM_ERROR_EXIT("list_add::malloc");
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
                {
                    free_compiler(o);
                    USAGE_ERROR_EXIT("Error, expected <dir> after -I\n%s", help);
                }
                include_dir = av[i];
            }
            else
                include_dir = &(av[i][2]);
            if (!list_add(&(o.include_dirs), include_dir))
            {
                free_compiler(o);
                SYSTEM_ERROR_EXIT("list_add::malloc");
            }
        }
        else if (!strcmp(av[i], "--help"))
            exit(printf("OVERVIEW: çc extensible GPL implementation that targets C99.\n\nUSAGE: çc [options] <inputs>\n\nOPTIONS:\n"
                        "-CC <value>            Define the C compiler and its flags\n"
                        "-D <macro>=<value>     Define <macro> to <value> (or 1 if <value> omitted)\n"
                        "-E                     Only run the preprocessor\n"
                        "-I <dir>               Add directory to include search path\n"
                        "-o <value>             "
                        "--help                 Display available options\n") &&
                 0);
        else
        {
            free_compiler(o);
            USAGE_ERROR_EXIT("Error, unknow çc flag : %s\n%s", av[i], help);
        }
        i += 1;
    }
    return (o);
}

/*
 * Exit codes : 
 *  0 - Normal exit
 *  1 - Usage error (USAGE_ERROR_CODE)
 *  2 - System error (SYSTEM_ERROR_CODE)
 */
int main(int ac, char **av)
{
    compiler_ctx ctx = parse_args(ac, av);
    int fd = open(ctx.file, O_RDONLY);
    if (fd < 0)
        SYSTEM_ERROR_EXIT("open");
    int len = lseek(fd, 0, SEEK_END);
    char *base_str;
    char *str = base_str = mmap(0, len, PROT_READ, MAP_PRIVATE, fd, 0);
    if (str == MAP_FAILED)
    {
        close(fd);
        SYSTEM_ERROR_EXIT("mmap");
    }
    char *new_str = 0;
    while (*str)
    {
        int k;
        k = try_register_macros(&ctx, &str);
        if (k < 0)
        {
            free(new_str);
            free_compiler(ctx);
            exit(k);
        }
        k = try_apply_macros(&ctx, &str);
        if (k < 0)
        {
            free(new_str);
            free_compiler(ctx);
            exit(k);
        }
        else if (!k)
        {
            char *swp = new_str;
            asprintf(&new_str, "%s%c", new_str ? new_str : "", *str);
            free(swp);
            cursor_incr(&ctx, &str, 1);
        }
    }
    if (!ctx.compile_c)
        printf("%s", new_str);
    else
    {
        char *cmd;
        asprintf(&cmd, "echo <<<\"EOF\"\n"
                       "%s\n"
                       "EOF >> %s && %s %s; rm -f %s;",
                 new_str, itermediate_file, ctx.cc, itermediate_file, itermediate_file);
        free(cmd);
    }
    free(new_str);
    close(fd);
}