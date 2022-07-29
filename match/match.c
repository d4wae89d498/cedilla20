#include "match.h"
#include "stdio.h"

char    *str_add_c(char **s, char c)
{
    char    *n;

    if (!*s)
        asprintf(&n, "%c", c);
    else 
    {
        asprintf(&n, "%s%c", *s, c);
        free(*s);
    }
    return *s = n;
}

char    *match(object_list **o, const char **str, ...)
{
    char        *r;
    va_list     ap;

    va_start(ap, str);
    r = vmatch(o, str, ap);
    va_end(ap);
    return r;
}

char    *vmatch(object_list **o, const char **str, va_list ap)
{
    char    *output;

    char    *current_arg;

    char    **capture_ptr;   
    char    *capture_type;
    int     (*until_func)(object_list **o, const char **str, va_list ap);

    output = 0;

    va_list     apc;    
    while (1)
    {
        current_arg = va_arg(ap, char *);
        if (!current_arg)
            return output;
        if (current_arg == capture)
        {
            printf("-- capturing...\n");
            capture_ptr = va_arg(ap, char**);
            capture_type = va_arg(ap, char*);
            if (capture_type == until)
            {
                printf("-- until...\n");
                until_func = va_arg(ap, void*);
                va_copy(apc, ap);
                while (!until_func(o, str, apc))
                {
                    str_add_c(capture_ptr, **str);
                    *str += 1;
                    va_copy(apc, ap);
                }
            }
            else 
            {
                printf("match error: unsupported capture type: %p\n", capture_type);
                exit(0);
            }
        }
        else 
        {
            if (strncmp(current_arg, *str, strlen(current_arg)))
            {
                    // restore object bkp 
            }
            else 
            {
                *str += strlen(current_arg);
            }
            //STRCMP
        }
    }
    return output;
}   