#ifndef VA_LISP_H
# define VA_LISP_H
#include "../list/list.h"
#include <stdarg.h>
typedef int(*va_function)(void *data, va_list ap);
int    vva_lisp(void *data, va_list ap);
int    va_lisp(void *data, ...);

#define lisp(B, ...) va_lisp(B, __VA_ARGS__, 0)
#endif