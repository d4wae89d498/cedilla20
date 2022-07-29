#include "object_list.h"
#include "stdio.h"

object_list *olist_last(object_list *l)
{
    return (object_list*)list_last((list*)l);
}

object_list *olist_new(object *data)
{
    return (object_list*)list_new(data);
}

object_list *olist_get(object_list *l, char *key)
{
    object_list     *it;

    it = l;
    while (it)
    {
        if (!strcmp(key, it->data->key))
            return (it);
        it = it->next;
    }
    return 0;
}

object *olist_get_object(object_list *l, char *key)
{
    object_list     *it;

    it = olist_get(l, key);
    if (it)
        return it->data;
    return 0;
}


object_list         *olist_set(object_list **l, object *data)
{
    object_list     *it;

    if (!data)
        return 0;
    if (!*l)
        return *l = olist_new(data);
    it = *l;
    while (it)
    {
        if (!strcmp(data->key, it->data->key))
        {
            object_free(it->data);
            it->data = data;
            return it;
        }
        if (it->next)
            it = it->next;
        else 
            break ;
    }
    return it->next = olist_new(data);
}

void                olist_del(object_list **l, char *key)
{
    object_list    *it;
    object_list    *swp;
    object_list    **prev;

    it = *l;
    prev = l;
    while (it)
    {
        swp = it->next;
        if (!strcmp(it->data->key, key))
        {
            object_free(it->data); 
            free(it);
            *prev = swp;
        }
        it = swp;
        if (it)
            prev = &(it->next);
    }
}

void olist_free(object_list *l)
{
    return list_free((list*)l, ((void(*)(void*))object_free));
}

object *get_object(object_list *l, char *key)
{
    object          *o;
    char            *key2;
    char            *cmatch;
    int             pos;

    cmatch = strchr(key, '.');
    if (!cmatch)
        return olist_get_object(l, key);
    pos = cmatch - key;
    key2 = strdup(key);
    key2[pos] = 0;
    o = olist_get_object(l, key2);
    free(key2);
    if (!o)
        return 0;
    if (strcmp(o->type, "object_list"))
    {
        printf("ERROR: GET ACCESS WITH WRONG TYPE, EXPECTED 'object_list' GOT '%s'\n", o->type);
        exit(1);
    }
    return get_object((object_list*)o->value, key + pos + 1);
}

object_list *set_object(object_list **l, char *key, object *v)
{
    object          *o;
    char            *key2;
    char            *cmatch;
    int             pos;

    cmatch = strchr(key, '.');
    if (!cmatch)
        return olist_set(l, v);
    pos = cmatch - key;
    key2 = strdup(key);
    key2[pos] = 0;
    o = olist_get_object(*l, key2);
    free(key2);
    if (!o)
    {
        olist_set(l, o = dobject_new("object_list", key2, 0, olist_free, olist_clone));
    }
    else if (strcmp(o->type, "object_list"))
    {
        printf("ERROR: GET ACCESS WITH WRONG TYPE, EXPECTED 'object_list' GOT '%s'\n", o->type);
        exit(1);
    }
    return set_object((object_list**)&(o->value), key + pos + 1, v);
}

object_list *olist_clone(object_list *l)
{
    object_list *o;
    object_list *it;

    o = 0;
    it = l;
    while (it)
    {
        olist_set(&o, object_clone(it->data));
        it = it->next;
    }
    return o;
}