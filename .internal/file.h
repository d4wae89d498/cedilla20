#ifndef CEDILLA_FILE_H
# define CEDILLA_FILE_H
# include <libc.h>

char *read_file(const char *);
char *read_fd(int);
void mkpath(const char *);

#endif