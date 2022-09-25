#ifndef IDE_COMPAT
# define IDE_COMPAT 1
#endif
#if !IDE_COMPAT
# define IDE_COMPAT_H 1
#else 
# include ".macro_cleaner.h"
#endif
#ifndef IDE_COMPAT_H
# define IDE_COMPAT_H
# define CEDILLA_CONCAT2(X, Y)  X##Y
# define CEDILLA_CONCAT(X, Y)   CEDILLA_CONCAT2(X, Y)
# define CEDILLA_STR2(X)         #X
# define CEDILLA_STR(X)        CEDILLA_STR2(X)
# define CEDILLA_CONCAT2(X, Y)  X##Y
# define CEDILLA_CONCAT(X, Y)   CEDILLA_CONCAT2(X, Y)
# define debugg(...) #__VA_ARGS__
# define each_test(x) , (x + 1)
# define dump_macro(...) printf("[%s:%i dump_macro] %s\n", __FILE__, __LINE__, apply(str, __VA_ARGS__));
# define cdump(...) message(apply(str, __VA_ARGS__))
# define macro CEDILLA_CONCAT(char * cedilla_macro_, __LINE__)(macro_list **macros, char **src, parser_ctx *ctx)
char        **src;
parser_ctx  ctx;
#endif