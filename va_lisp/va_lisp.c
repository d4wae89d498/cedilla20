#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "va_lisp.h"

int vva_lisp(void *data, va_list ap)
{
    va_function f;

    int r;

    r = 0;
    while (1)
    {
        f = (va_function) va_arg(ap, void*);
        if (!f)
            return 1;
        r = r || (f(data, ap));
        if (r)
            return r;
    }
}

int va_lisp(void *data, ...)
{
    va_list ap;
    int r;

    va_start(ap, data);
    r = vva_lisp(data, ap);
    va_end(ap);
    return r;
}
