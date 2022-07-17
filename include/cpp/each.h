#ifndef CPP_EACH
# define CPP_EACH
# include "../templates/cpp_foreach_helper.h"
# include "cpp_count.h"
# include <libc.h>
# define CPP_EACH(M, ...) apply(CPP_CONCAT, CPP_EACH_, va_count(__VA_ARGS__))(M, __VA_ARGS__)
#endif
