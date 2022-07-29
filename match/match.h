#ifndef MATCH_H
# define MATCH_H
# include "object_list.h"
# include "stdarg.h"

const char  *until = "__CEDILLA__UNTIL";
const char  *capture = "__CEDILLA__CAPTURE";

char    *match(object_list **, char **str, ...);
char    *vmatch(object_list **, char **str, va_list);
#endif