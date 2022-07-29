#ifndef OBJECT_H
# define OBJECT_H
# include "string.h"
# include "stdlib.h"
# include "list.h"
# define             object_new(A, B, C) _object_new(A, B, (long long)C)
# define             dobject_new(A, B, C, D) _dobject_new(A, B, (long long) C, D)

typedef struct s_object
{
    char            *key;
    char            *type;
    long long       value;
    void            (*value_destructor)(void*);
}   object;



object              *_object_new(char *type, char *key, long long value);
object              *_dobject_new(char *type, char *key, long long value, void (*value_destructor)(void*));
void                object_free(object *p);




#endif