#ifndef CEDILLA_H
# define CEDILLA_H
# ifndef PATH_SIZE
#  define PATH_SIZE 512
# endif
# include "list.h"

# define _ (void*)(long long)!!

extern char  cwd[PATH_SIZE];

#endif