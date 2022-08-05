#include "va_lisp.h"

#include <stdio.h>

int   print_5(void*data, va_list ap)
{
    (void) ap;
    (void) data;
    printf("5\n");
    return 0;
}

int   print_int(void*data, va_list ap)
{
    (void) ap;
    (void) data;
    printf("%i\n", va_arg(ap, int ));
    return 0;
}


int main()
{
    int         data = 0;

    lisp(&data, print_5, print_int, 10, print_int, 10);
}
