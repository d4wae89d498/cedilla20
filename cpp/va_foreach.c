#ifndef VA_FOREACH
# define VA_FOREACH
# include "../cpp-state-machine-generator/out.h"
# include "va_count.h"
# include <libc.h>
/*
 * C99 standard : 
 * 5.2.4.1 Translation limits
 *      The implementation shall be able to translate and execute at least one
 *      program that contains at least one instance of every one of the
 *      following limits:
 *      ...
 *      — 127 parameters in one function definition
 *      — 127 arguments in one function cal
 *      ...
 *      — 127 arguments in one macro invocation
 */
#define concat(X, Y) X##Y
#define concat2(X, Y) concat(X, Y)
#define va_each(M, ...) concat2(va_each_, va_count(__VA_ARGS__))(M, __VA_ARGS__)
#define str(...) #__VA_ARGS__
#define str_expand(...) str(__VA_ARGS__)
#define each_test(x) , (x + 1)
#define dump_macro(...) printf("[%s:%i dump_macro] %s\n", __FILE__, __LINE__, str_expand(__VA_ARGS__));
int main()
{
    printf("%i %i\n" va_each(each_test, 1, 2));
    dump_macro(va_each(each_test, 1, 2));

}
#endif
