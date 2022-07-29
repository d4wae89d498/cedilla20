#include "match.c"

int     is_str(object_list **o, char **str, va_list ap)
{
    char    *arg;

    arg = va_arg(ap, char*);

    return !(strncmp(arg, *str, strlen(arg)));
}

int main()
{
    char *str = "int g(int x);";
    object_list *o = 0;

    char   *s; 
    match (&o, &str,
            capture, &s, until, is_str, ")",
        0
    );

    printf("CAPTURE : %s\n", s);

}