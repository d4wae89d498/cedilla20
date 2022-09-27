#ifndef IDE_COMPAT
# define IDE_COMPAT 1
#endif
#if IDE_COMPAT
# include ".macro_cleaner.h"
# ifndef IDE_COMPAT_H
#  define IDE_COMPAT_H
#  define CEDILLA_CONCAT2(X, Y)  X##Y
#  define CEDILLA_CONCAT(X, Y)   CEDILLA_CONCAT2(X, Y)
#  define macro CEDILLA_CONCAT(char * cedilla_macro_, __LINE__)(macro_list **macros, char **src, compiler_ctx *ctx)
char        **src;
compiler_ctx  ctx;
# endif
#endif