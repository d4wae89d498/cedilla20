#include "list.h"

list    *list_new(void *d)
{
    list    *o;

    o = malloc(sizeof(list));
    o->data = d;
    o->next = 0;
    return (o);
}

void    list_add(list **l, list *e)
{
    list    *i;

    if (!*l)
    {
        *l = e;
        return ;
    }
    i = *l;
    while (i) 
    {
        if (!i->next)
        {
            i->next = e;
            return ;
        }
        i = i->next;
    }    
    i->next = e;
}

list    *list_add_data(list **l, void *d)
{
    list    *o;

    o = list_new(d);
    list_add(l, o);
    return (o);
}

void    *list_find(list *l, void*(*f)(void *, void*), void *data)
{
    list    *i;
    void    *d;

    i = l;
    while (i)
    {
        d = f(i->data, data);
        if (d)
            return (d);
        i = i->next;
    }
    return (0);
}

void    list_delete(list **l, void (*f)(void*))
{
    list    *i;
    list    *swp;

    i = *l; 
    while (i)
    {
        swp = i->next;        
        f(i->data);
        free(i);
        i = swp;        
    }  
    *l = 0;
}
