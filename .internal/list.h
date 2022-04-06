#ifndef CEDILLA_LIST_H
# define CEDILLA_LIST_H
# include <libc.h>

typedef struct s_list
{
    void            *data;
    struct  s_list  *next;
}  list;

list    *list_new(void *);
void    list_add(list **, list *);
list    *list_add_data(list **, void *);
void    *list_find(list *, void*(*)(void *, void *), void *data);
void    list_delete(list **, void(*)(void*));

#endif