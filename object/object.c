#include "object.h"

object *_object_new(char *type, char *key, long long value)
{
    return _dobject_new(type, key, value, 0);
}

object *_dobject_new(char *type, char *key, long long value, void (*value_destructor)(void *))
{
    object *o;

    o = (object *)malloc(sizeof(object));
    o->type = strdup(type);
    o->key = strdup(key);
    o->value = value;
    o->value_destructor = value_destructor;
    return o;
}

void object_free(object *p)
{
    object *o;

    o = p;
    if (!o)
        return;
    free(o->key);
    free(o->type);
    if (o->value_destructor)
        o->value_destructor((void *)o->value);
    free(p);
}