#include "./string.h"

int str_append(char **ptr, char c)
{
    char    *swp;

    swp = *ptr;
    if (*ptr)
        asprintf(ptr, "%s%c", *ptr, c);
    else 
        asprintf(ptr, "%c", c);
    free(swp);
    return (!!ptr);
}