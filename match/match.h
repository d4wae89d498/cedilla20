#ifndef MATCH_H
# define MATCH_H
# include "object_list.h"
# include "stdarg.h"
const char *limit = "__CEDILLA_LIMIT"

# define limit      ,limit,
# define token      "__CEDILLA_STATE_PARSE",
# define call       "__CEDILLA_STATE_CALL",
# define skip       "__CEDILLA_SKIP",
# define oskip      "__CEDILLA_OSKIP",
# define until      ,"__CEDILLA__UNTIL",
# define capture    "__CEDILLA__CAPTURE",
# define _          ,

char    *match(object_list **, const char **str, ...);
char    *vmatch(object_list **, const char **str, va_list);
#endif