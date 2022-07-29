#include "list.h"

list    *list_last(list *l)
{
    while (l)
    {
        if (!l->next)
            return l;
        l = l->next;
    }
    return 0;
}

list    *list_new(void *data)
{
    list *o;

    o = malloc(sizeof(list));
    o->data = data;
    o->next = 0;
    return o;
}

list    *list_add(list **l, void *data)
{
    list *last;

    last = list_last(*l);
    if (!last)
        return *l = list_new(data);
    return last->next = list_new(data);
}

void   list_del(list **l, list *k, void(*value_destructor)(void*))
{
    list    *it;
    list    *swp;
    list    **prev;

    it = *l;
    prev = l;
    while (it)
    {
        swp = it->next;
        if (it == k)
        {
            if (value_destructor)
                value_destructor(it->data);
            free(it);
            *prev = swp;
        }
        it = swp;
        if (it)
            prev = &(it->next);
    }
}

void    list_free(list **l, void(*value_destructor)(void*))
{
    list    *it;
    list    *swp;

    it = *l;
    while (it)
    {
        swp = it->next;
        if (value_destructor)
            value_destructor(it->data);
        free(it);
        it = swp;
    }
    *l = 0;
}