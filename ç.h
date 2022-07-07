#ifndef CEDILLA_H
# define CEDILLA_H
# include <libc.h>
# include "./match/match.h"
# define CONCAT2(X, Y)  X##Y
# define CONCAT(X, Y)   CONCAT2(X, Y)
# define STRINGIFY2(X)  #X
# define STRINGIFY(X)   STRINGIFY2(X)
# define auto           __auto_type
# define compile_time
# define macro          CONCAT(char * r_, __LINE__)(ç_ctx ctx)

#endif