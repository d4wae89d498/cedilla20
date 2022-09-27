#ifndef OBJECT_H
# define OBJECT_H
# include <string.h>
# include <stdlib.h>
# include "list.h"
# define STR(X) #X
# define             object_new(TYPE, KEY, VALUE) _object_new(TYPE, KEY, (long long)VALUE)
# define             new(TYPE, KEY, VALUE) object_new(STR(TYPE), STR(KEY), VALUE)      
# define             dobject_new(TYPE, KEY, VALUE, DESTRUCT, CLONE) _dobject_new(TYPE, KEY, (long long) VALUE, (void*)DESTRUCT, (void*)CLONE)
# define             dnew(TYPE, KEY, VALUE, DESTRUCT, CLONE) dobject_new(STR(TYPE), STR(KEY), VALUE, DESTRUCT, CLONE)      
// todo:: add const types 
typedef struct s_object
{
    char            *key;
    char            *type;
    long long       value;
    void            (*value_destruct)(void*);
    void            *(*value_clone)(void*);
}   object;
object              *_object_new(char *type, char *key, long long value);
object              *_dobject_new(char *type, char *key, long long value, void (*value_destruct)(void*), void*(*value_clone)(void*));
void                object_free(object *p);
object              *object_clone(object *o);
#endif