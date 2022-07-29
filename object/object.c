#include "object.h"

object *_object_new(char *type, char *key, long long value)
{
    return _dobject_new(type, key, value, 0, 0);
}

object *_dobject_new(char *type, char *key, long long value, void (*value_destruct)(void *), void*(*value_clone)(void*))
{
    object *o;

    o = (object *)malloc(sizeof(object));
    o->type = strdup(type);
    o->key = strdup(key);
    o->value = value;
    o->value_destruct = value_destruct;
    o->value_clone = value_clone;
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
    if (o->value_destruct)
        o->value_destruct((void *)o->value);
    free(p);
}

object  *object_clone(object *o)
{
    if (o->value_clone)
        return dobject_new(o->type, o->key, o->value_clone((void*)o->value), o->value_destruct, o->value_clone);
    return dobject_new(o->type, o->key, o->value, o->value_destruct, o->value_clone); 
}