#ifndef CEDILLA
# define CEDILLA
# ifndef ide_compat
#  define ide_compat 1
# endif
# ifndef CEDILLA_TEST
#  define CEDILLA_TEST 0
# endif
# if CEDILLA_TEST == 1
#  include "assert.h"
# endif
# include "../src/ç/macro.ç"
# include "../src/ç/define.ç"
#endif
#if ide_compat == 1
#  include "../cpp-templates/ç_macro_cleaner.h"
#endif
